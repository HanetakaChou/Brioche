//
// Copyright (C) YuqiaoZhang(HanetakaChou)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef _BRX_VK_DEVICE_H_
#define _BRX_VK_DEVICE_H_ 1

#include "../include/brx_device.h"
#include "../thirdparty/McRT-Malloc/include/mcrt_vector.h"
#if defined(__GNUC__)
#if defined(__linux__)
#if defined(__ANDROID__)
#define VK_USE_PLATFORM_ANDROID_KHR 1
#else
#define VK_USE_PLATFORM_XCB_KHR 1
#endif
#else
#error Unknown Platform
#endif
#elif defined(_MSC_VER)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 1
#define VK_USE_PLATFORM_WIN32_KHR 1
#include <sdkddkver.h>
#include <windows.h>
#else
#error Unknown Compiler
#endif
#include "../thirdparty/Vulkan-Headers/include/vulkan/vulkan.h"
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wnullability-completeness"
#endif
#include "../thirdparty/VulkanMemoryAllocator/include/vk_mem_alloc.h"
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

extern VkPipelineStageFlags const g_graphics_queue_family_graphics_compute_pipeline_shader_read_stages;
extern VkPipelineStageFlags const g_graphics_queue_family_ray_tracing_pipeline_shader_read_stages;
extern VkPipelineStageFlags const g_graphics_queue_family_acceleration_structure_build_shader_read_stages;

class brx_vk_device final : public brx_device
{

#if defined(__GNUC__)
#if defined(__linux__)
    void *m_dynamic_library_vulkan;
#else
#error Unknown Platform
#endif
#elif defined(_MSC_VER)
    HINSTANCE m_dynamic_library_vulkan;
#else
#error Unknown Compiler
#endif

    PFN_vkGetInstanceProcAddr m_pfn_get_instance_proc_addr;

    bool m_support_ray_tracing;

    VkAllocationCallbacks *m_allocation_callbacks;

    VkInstance m_instance;

#ifndef NDEBUG
    VkDebugUtilsMessengerEXT m_messenge;
#endif

    VkPhysicalDevice m_physical_device;
    uint32_t m_min_uniform_buffer_offset_alignment;
    uint32_t m_min_storage_buffer_offset_alignment;
    uint32_t m_optimal_buffer_copy_offset_alignment;
    uint32_t m_optimal_buffer_copy_row_pitch_alignment;

    bool m_has_dedicated_upload_queue;
    uint32_t m_graphics_queue_family_index;
    uint32_t m_upload_queue_family_index;

    PFN_vkGetDeviceProcAddr m_pfn_get_device_proc_addr;
    bool m_physical_device_feature_texture_compression_BC;
    bool m_physical_device_feature_texture_compression_ASTC_LDR;
    VkDevice m_device;

    VkQueue m_graphics_queue;
    VkQueue m_upload_queue;

    VkFormat m_depth_attachment_image_format;
    VkFormat m_depth_stencil_attachment_image_format;
    bool m_depth_attachment_image_format_support_sampled_image;
    bool m_depth_stencil_attachment_image_format_support_sampled_image;

    VmaAllocator m_memory_allocator;

    VmaPool m_uniform_upload_buffer_memory_pool;
    VmaPool m_staging_upload_buffer_memory_pool;
    VmaPool m_storage_intermediate_buffer_memory_pool;
    VmaPool m_storage_asset_buffer_memory_pool;
    VmaPool m_color_transient_attachment_image_memory_pool;
    VmaPool m_color_attachment_sampled_image_memory_pool;
    VmaPool m_depth_transient_attachment_image_memory_pool;
    VmaPool m_depth_attachment_sampled_image_memory_pool;
    VmaPool m_depth_stencil_transient_attachment_image_memory_pool;
    VmaPool m_depth_stencil_attachment_sampled_image_memory_pool;
    VmaPool m_storage_intermediate_image_memory_pool;
    VmaPool m_sampled_asset_image_memory_pool;
    VmaPool m_scratch_buffer_memory_pool;
    VmaPool m_intermediate_bottom_level_acceleration_structure_memory_pool;
    VmaPool m_non_compacted_bottom_level_acceleration_structure_memory_pool;
    VmaPool m_compacted_bottom_level_acceleration_structure_memory_pool;
    VmaPool m_top_level_acceleration_structure_instance_upload_buffer_memory_pool;
    VmaPool m_top_level_acceleration_structure_memory_pool;

    PFN_vkWaitForFences m_pfn_wait_for_fences;
    PFN_vkResetFences m_pfn_reset_fences;
    PFN_vkResetCommandPool m_pfn_reset_command_pool;
    PFN_vkAcquireNextImageKHR m_pfn_acquire_next_image;
    PFN_vkCreateImageView m_pfn_create_image_view;
    PFN_vkDestroyImageView m_pfn_destroy_image_view;
    PFN_vkGetBufferDeviceAddressKHR m_pfn_get_buffer_device_address;
    PFN_vkCreateAccelerationStructureKHR m_pfn_create_acceleration_structure;
    PFN_vkDestroyAccelerationStructureKHR m_pfn_destroy_acceleration_structure;
    PFN_vkGetAccelerationStructureDeviceAddressKHR m_pfn_get_acceleration_structure_device_address;
    PFN_vkGetQueryPoolResults m_pfn_get_query_pool_results;

public:
    brx_vk_device();
    void init(void *wsi_connection, bool support_ray_tracing);
    void uninit();
    ~brx_vk_device();
    brx_graphics_queue *create_graphics_queue() const override;
    void destroy_graphics_queue(brx_graphics_queue *graphics_queue) const override;
    brx_upload_queue *create_upload_queue() const override;
    void destroy_upload_queue(brx_upload_queue *upload_queue) const override;
    brx_graphics_command_buffer *create_graphics_command_buffer() const override;
    void reset_graphics_command_buffer(brx_graphics_command_buffer *graphics_command_buffer) const override;
    void destroy_graphics_command_buffer(brx_graphics_command_buffer *graphics_command_buffer) const override;
    brx_upload_command_buffer *create_upload_command_buffer() const override;
    void reset_upload_command_buffer(brx_upload_command_buffer *upload_command_buffer) const override;
    void destroy_upload_command_buffer(brx_upload_command_buffer *upload_command_buffer) const override;
    brx_fence *create_fence(bool signaled) const override;
    void wait_for_fence(brx_fence *fence) const override;
    void reset_fence(brx_fence *fence) const override;
    void destroy_fence(brx_fence *fence) const override;
    brx_descriptor_set_layout *create_descriptor_set_layout(uint32_t descriptor_set_binding_count, BRX_DESCRIPTOR_SET_LAYOUT_BINDING const *descriptor_set_bindings) const override;
    void destroy_descriptor_set_layout(brx_descriptor_set_layout *descriptor_set_layout) const override;
    brx_pipeline_layout *create_pipeline_layout(uint32_t descriptor_set_layout_count, brx_descriptor_set_layout const *const *descriptor_set_layouts) const override;
    void destroy_pipeline_layout(brx_pipeline_layout *pipeline_layout) const override;
    brx_descriptor_set *create_descriptor_set(brx_descriptor_set_layout const *descriptor_set_layout) override;
    void write_descriptor_set(brx_descriptor_set *descriptor_set, uint32_t dst_binding, BRX_DESCRIPTOR_TYPE descriptor_type, uint32_t dst_descriptor_start_index, uint32_t src_descriptor_count, brx_uniform_upload_buffer const *const *src_dynamic_uniform_buffers, uint32_t const *src_dynamic_uniform_buffer_ranges, brx_read_only_storage_buffer const *const *src_read_only_storage_buffers, brx_storage_buffer const *const *src_storage_buffers, brx_sampled_image const *const *src_sampled_images, brx_storage_image const *const *src_storage_images, brx_sampler const *const *src_samplers, brx_top_level_acceleration_structure const *const *src_top_level_acceleration_structures) const override;
    void destroy_descriptor_set(brx_descriptor_set *descriptor_set) override;
    brx_render_pass *create_render_pass(uint32_t color_attachment_count, BRX_RENDER_PASS_COLOR_ATTACHMENT const *color_attachments, BRX_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT const *depth_stencil_attachment) const override;
    void destroy_render_pass(brx_render_pass *render_pass) const override;
    brx_graphics_pipeline *create_graphics_pipeline(brx_render_pass const *render_pass, brx_pipeline_layout const *pipeline_layout, size_t vertex_shader_module_code_size, void const *vertex_shader_module_code, size_t fragment_shader_module_code_size, void const *fragment_shader_module_code, bool depth_enable, BRX_GRAPHICS_PIPELINE_COMPARE_OPERATION depth_compare_operation) const override;
    void destroy_graphics_pipeline(brx_graphics_pipeline *graphics_pipeline) const override;
    brx_compute_pipeline *create_compute_pipeline(brx_pipeline_layout const *pipeline_layout, size_t compute_shader_module_code_size, void const *compute_shader_module_code) const override;
    void destroy_compute_pipeline(brx_compute_pipeline *compute_pipeline) const override;
    brx_frame_buffer *create_frame_buffer(brx_render_pass const *render_pass, uint32_t width, uint32_t height, uint32_t color_attachment_count, brx_color_attachment_image const *const *color_attachments, brx_depth_stencil_attachment_image const *depth_stencil_attachment) const override;
    void destroy_frame_buffer(brx_frame_buffer *frame_buffer) const override;
    uint32_t get_uniform_upload_buffer_offset_alignment() const override;
    brx_uniform_upload_buffer *create_uniform_upload_buffer(uint32_t size) const override;
    void destroy_uniform_upload_buffer(brx_uniform_upload_buffer *uniform_upload_buffer) const override;
    uint32_t get_staging_upload_buffer_offset_alignment() const override;
    uint32_t get_staging_upload_buffer_row_pitch_alignment() const override;
    brx_staging_upload_buffer *create_staging_upload_buffer(uint32_t size) const override;
    void destroy_staging_upload_buffer(brx_staging_upload_buffer *staging_upload_buffer) const override;
    brx_storage_intermediate_buffer *create_storage_intermediate_buffer(uint32_t size) const override;
    void destroy_storage_intermediate_buffer(brx_storage_intermediate_buffer *storage_intermediate_buffer) const override;
    brx_storage_asset_buffer *create_storage_asset_buffer(uint32_t size) const override;
    void destroy_storage_asset_buffer(brx_storage_asset_buffer *asset_storage_buffer) const override;
    brx_color_attachment_image *create_color_attachment_image(BRX_COLOR_ATTACHMENT_IMAGE_FORMAT color_attachment_image_format, uint32_t width, uint32_t height, bool allow_sampled_image) const override;
    void destroy_color_attachment_image(brx_color_attachment_image *color_attachment_image) const override;
    BRX_DEPTH_STENCIL_ATTACHMENT_IMAGE_FORMAT get_depth_attachment_image_format() const override;
    BRX_DEPTH_STENCIL_ATTACHMENT_IMAGE_FORMAT get_depth_stencil_attachment_image_format() const override;
    brx_depth_stencil_attachment_image *create_depth_stencil_attachment_image(BRX_DEPTH_STENCIL_ATTACHMENT_IMAGE_FORMAT depth_stencil_attachment_image_format, uint32_t width, uint32_t height, bool allow_sampled_image) const override;
    void destroy_depth_stencil_attachment_image(brx_depth_stencil_attachment_image *depth_stencil_attachment_image) const override;
    brx_storage_image *create_storage_image(BRX_STORAGE_IMAGE_FORMAT storage_image_format, uint32_t width, uint32_t height, bool allow_sampled_image) const override;
    void destroy_storage_image(brx_storage_image *storage_image) const override;
    bool is_sampled_asset_image_compression_bc_supported() const override;
    bool is_sampled_asset_image_compression_astc_supported() const override;
    brx_sampled_asset_image *create_sampled_asset_image(BRX_SAMPLED_ASSET_IMAGE_FORMAT sampled_asset_image_format, uint32_t width, uint32_t height, uint32_t mip_levels) const override;
    void destroy_sampled_asset_image(brx_sampled_asset_image *sampled_asset_image) const override;
    brx_sampler *create_sampler(BRX_SAMPLER_FILTER filter) const override;
    void destroy_sampler(brx_sampler *sampler) const override;
    brx_surface *create_surface(void *wsi_window) const override;
    void destroy_surface(brx_surface *surface) const override;
    brx_swap_chain *create_swap_chain(brx_surface *surface) const override;
    bool acquire_next_image(brx_graphics_command_buffer *graphics_command_buffer, brx_swap_chain const *swap_chain, uint32_t *out_swap_chain_image_index) const override;
    void destroy_swap_chain(brx_swap_chain *swap_chain) const override;
    brx_scratch_buffer *create_scratch_buffer(uint32_t size) const override;
    void destroy_scratch_buffer(brx_scratch_buffer *scratch_buffer) const override;
    void get_intermediate_bottom_level_acceleration_structure_size(uint32_t bottom_level_acceleration_structure_geometry_count, BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY const *bottom_level_acceleration_structure_geometries, uint32_t *intermediate_bottom_level_acceleration_structure_size, uint32_t *build_scratch_size, uint32_t *update_scratch_size) const override;
    brx_intermediate_bottom_level_acceleration_structure *create_intermediate_bottom_level_acceleration_structure(uint32_t size) const override;
    void destroy_intermediate_bottom_level_acceleration_structure(brx_intermediate_bottom_level_acceleration_structure *intermediate_bottom_level_acceleration_structure) const override;
    void get_non_compacted_bottom_level_acceleration_structure_size(uint32_t acceleration_structure_geometry_count, BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY const *acceleration_structure_geometries, uint32_t *acceleration_structure_size, uint32_t *build_scratch_size) const override;
    brx_non_compacted_bottom_level_acceleration_structure *create_non_compacted_bottom_level_acceleration_structure(uint32_t size) const override;
    void destroy_non_compacted_bottom_level_acceleration_structure(brx_non_compacted_bottom_level_acceleration_structure *non_compacted_bottom_level_acceleration_structure) const override;
    brx_compacted_bottom_level_acceleration_structure_size_query_pool *create_compacted_bottom_level_acceleration_structure_size_query_pool(uint32_t query_count) const override;
    uint32_t get_compacted_bottom_level_acceleration_structure_size_query_pool_result(brx_compacted_bottom_level_acceleration_structure_size_query_pool const *compacted_bottom_level_acceleration_structure_size_query_pool, uint32_t query_index) const override;
    void destroy_compacted_bottom_level_acceleration_structure_size_query_pool(brx_compacted_bottom_level_acceleration_structure_size_query_pool *compacted_bottom_level_acceleration_structure_size_query_pool) const override;
    brx_compacted_bottom_level_acceleration_structure *create_compacted_bottom_level_acceleration_structure(uint32_t size) const override;
    void destroy_compacted_bottom_level_acceleration_structure(brx_compacted_bottom_level_acceleration_structure *compacted_bottom_level_acceleration_structure) const override;
    brx_top_level_acceleration_structure_instance_upload_buffer *create_top_level_acceleration_structure_instance_upload_buffer(uint32_t instance_count) const override;
    void destroy_top_level_acceleration_structure_instance_upload_buffer(brx_top_level_acceleration_structure_instance_upload_buffer *top_level_acceleration_structure_instance_upload_buffer) const override;
    void get_top_level_acceleration_structure_size(uint32_t top_level_acceleration_structure_instance_count, uint32_t *top_level_acceleration_structure_size, uint32_t *build_scratch_size, uint32_t *update_scratch_size) const override;
    brx_top_level_acceleration_structure *create_top_level_acceleration_structure(uint32_t size) const override;
    void destroy_top_level_acceleration_structure(brx_top_level_acceleration_structure *top_level_acceleration_structure) const override;
};

class brx_vk_graphics_queue final : public brx_graphics_queue
{
    VkQueue m_graphics_queue;

    bool m_has_dedicated_upload_queue;
    uint32_t m_upload_queue_family_index;
    uint32_t m_graphics_queue_family_index;

    PFN_vkQueueSubmit m_pfn_queue_submit;
    PFN_vkQueuePresentKHR m_pfn_queue_present;

public:
    brx_vk_graphics_queue(bool has_dedicated_upload_queue, uint32_t upload_queue_family_index, uint32_t graphics_queue_family_index, VkQueue graphics_queue, PFN_vkQueueSubmit pfn_queue_submit, PFN_vkQueuePresentKHR pfn_queue_present);
    void wait_and_submit(brx_upload_command_buffer const *upload_command_buffer, brx_graphics_command_buffer const *graphics_command_buffer, brx_fence *fence) const override;
    bool submit_and_present(brx_graphics_command_buffer *graphics_command_buffer, brx_swap_chain *swap_chain, uint32_t swap_chain_image_index, brx_fence *fence) const override;
    void steal(VkQueue *out_graphics_queue);
    ~brx_vk_graphics_queue();
};

class brx_vk_upload_queue final : public brx_upload_queue
{
    VkQueue m_upload_queue;

    bool m_has_dedicated_upload_queue;
    uint32_t m_upload_queue_family_index;
    uint32_t m_graphics_queue_family_index;

    PFN_vkQueueSubmit m_pfn_queue_submit;

public:
    brx_vk_upload_queue(bool has_dedicated_upload_queue, uint32_t upload_queue_family_index, uint32_t graphics_queue_family_index, VkQueue upload_queue, PFN_vkQueueSubmit pfn_queue_submit);
    void submit_and_signal(brx_upload_command_buffer const *upload_command_buffer) const override;
    void steal(VkQueue *out_upload_queue);
    ~brx_vk_upload_queue();
};

class brx_vk_graphics_command_buffer final : public brx_graphics_command_buffer
{
    bool m_support_ray_tracing;

    bool m_has_dedicated_upload_queue;
    uint32_t m_graphics_queue_family_index;
    uint32_t m_upload_queue_family_index;

    VkCommandPool m_command_pool;
    VkCommandBuffer m_command_buffer;

    VkSemaphore m_acquire_next_image_semaphore;
    VkSemaphore m_queue_submit_semaphore;

    PFN_vkBeginCommandBuffer m_pfn_begin_command_buffer;
    PFN_vkCmdPipelineBarrier m_pfn_cmd_pipeline_barrier;
#ifndef NDEBUG
    PFN_vkCmdBeginDebugUtilsLabelEXT m_pfn_cmd_begin_debug_utils_label;
    PFN_vkCmdEndDebugUtilsLabelEXT m_pfn_cmd_end_debug_utils_label;
#endif
    PFN_vkCmdBeginRenderPass m_pfn_cmd_begin_render_pass;
    PFN_vkCmdBindPipeline m_pfn_cmd_bind_pipeline;
    PFN_vkCmdSetViewport m_pfn_cmd_set_view_port;
    PFN_vkCmdSetScissor m_pfn_cmd_set_scissor;
    PFN_vkCmdBindDescriptorSets m_pfn_cmd_bind_descriptor_sets;
    PFN_vkCmdBindVertexBuffers m_pfn_cmd_bind_vertex_buffers;
    PFN_vkCmdBindIndexBuffer m_pfn_cmd_bind_index_buffer;
    PFN_vkCmdDraw m_pfn_cmd_draw;
    PFN_vkCmdDrawIndexed m_pfn_cmd_draw_indexed;
    PFN_vkCmdEndRenderPass m_pfn_cmd_end_render_pass;
    PFN_vkCmdDispatch m_pfn_cmd_dispatch;
    PFN_vkCmdBuildAccelerationStructuresKHR m_pfn_cmd_build_acceleration_structure;
    PFN_vkEndCommandBuffer m_pfn_end_command_buffer;

public:
    brx_vk_graphics_command_buffer();
    void init(bool support_ray_tracing, bool has_dedicated_upload_queue, uint32_t graphics_queue_family_index, uint32_t upload_queue_family_index, PFN_vkGetInstanceProcAddr pfn_get_instance_proc_addr, VkInstance instance, PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks);
    void uninit(PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks);
    ~brx_vk_graphics_command_buffer();
    VkCommandPool get_command_pool() const;
    VkCommandBuffer get_command_buffer() const;
    VkSemaphore get_acquire_next_image_semaphore() const;
    VkSemaphore get_queue_submit_semaphore() const;
    void begin() override;
    void acquire(uint32_t storage_asset_buffer_count, brx_storage_asset_buffer const *const *storage_asset_buffers, uint32_t sampled_asset_image_count, brx_sampled_asset_image const *const *sampled_asset_images, uint32_t const *dst_mip_levels, uint32_t compacted_bottom_level_acceleration_structure_count, brx_compacted_bottom_level_acceleration_structure const *const *compacted_bottom_level_acceleration_structures) override;
    void begin_debug_utils_label(char const *label_name) override;
    void end_debug_utils_label() override;
    void begin_render_pass(brx_render_pass const *render_pass, brx_frame_buffer const *frame_buffer, uint32_t width, uint32_t height, uint32_t color_clear_value_count, float const (*color_clear_values)[4], float const *depth_clear_value, uint8_t const *stencil_clear_value) override;
    void bind_graphics_pipeline(brx_graphics_pipeline const *graphics_pipeline) override;
    void set_view_port(uint32_t width, uint32_t height) override;
    void set_scissor(uint32_t width, uint32_t height) override;
    void bind_graphics_descriptor_sets(brx_pipeline_layout const *pipeline_layout, uint32_t descriptor_set_count, brx_descriptor_set const *const *descriptor_sets, uint32_t dynamic_offet_count, uint32_t const *dynamic_offsets) override;
    void draw(uint32_t vertex_count, uint32_t instance_count) override;
    void end_render_pass() override;
    void compute_pass_load(uint32_t storage_buffer_count, brx_storage_buffer const *const *storage_buffers, BRX_COMPUTE_PASS_STORAGE_BUFFER_LOAD_OPERATION const *storage_buffer_load_operations, uint32_t storage_image_count, brx_storage_image const *const *storage_images, BRX_COMPUTE_PASS_STORAGE_IMAGE_LOAD_OPERATION const *storage_image_load_operations) override;
    void bind_compute_pipeline(brx_compute_pipeline const *compute_pipeline) override;
    void bind_compute_descriptor_sets(brx_pipeline_layout const *pipeline_layout, uint32_t descriptor_set_count, brx_descriptor_set const *const *descriptor_sets, uint32_t dynamic_offet_count, uint32_t const *dynamic_offsets) override;
    void dispatch(uint32_t group_count_x, uint32_t group_count_y, uint32_t group_count_z) override;
    void compute_pass_store(uint32_t storage_buffer_count, brx_storage_buffer const *const *storage_buffers, BRX_COMPUTE_PASS_STORAGE_BUFFER_STORE_OPERATION const *storage_buffer_store_operations, uint32_t storage_image_count, brx_storage_image const *const *storage_images, BRX_COMPUTE_PASS_STORAGE_IMAGE_STORE_OPERATION const *storage_image_store_operations) override;
    void build_intermediate_bottom_level_acceleration_structure(brx_intermediate_bottom_level_acceleration_structure *intermediate_bottom_level_acceleration_structure, uint32_t bottom_level_acceleration_structure_geometry_count, BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY const *bottom_level_acceleration_structure_geometries, brx_scratch_buffer *scratch_buffer) override;
    void build_intermediate_bottom_level_acceleration_structure_store(uint32_t intermediate_bottom_level_acceleration_structure_count, brx_intermediate_bottom_level_acceleration_structure const *const *intermediate_bottom_level_acceleration_structures) override;
    void update_intermediate_bottom_level_acceleration_structure(brx_intermediate_bottom_level_acceleration_structure *intermediate_bottom_level_acceleration_structure, brx_acceleration_structure_build_input_read_only_buffer const *const *bottom_level_acceleration_structure_geometry_vertex_position_buffers, brx_scratch_buffer *scratch_buffer) override;
    void update_intermediate_bottom_level_acceleration_structure_store(uint32_t intermediate_bottom_level_acceleration_structure_count, brx_intermediate_bottom_level_acceleration_structure const *const *intermediate_bottom_level_acceleration_structures) override;
    void build_top_level_acceleration_structure(brx_top_level_acceleration_structure *top_level_acceleration_structure, uint32_t top_level_acceleration_structure_instance_count, brx_top_level_acceleration_structure_instance_upload_buffer *top_level_acceleration_structure_instance_upload_buffer, brx_scratch_buffer *scratch_buffer) override;
    void build_top_level_acceleration_structure_store(brx_top_level_acceleration_structure *top_level_acceleration_structure) override;
    void update_top_level_acceleration_structure(brx_top_level_acceleration_structure *top_level_acceleration_structure, brx_top_level_acceleration_structure_instance_upload_buffer *top_level_acceleration_structure_instance_upload_buffer, brx_scratch_buffer *scratch_buffer) override;
    void update_top_level_acceleration_structure_store(brx_top_level_acceleration_structure *top_level_acceleration_structure) override;
    void end() override;
};

class brx_vk_upload_command_buffer final : public brx_upload_command_buffer
{
    bool m_support_ray_tracing;

    bool m_has_dedicated_upload_queue;
    uint32_t m_graphics_queue_family_index;
    uint32_t m_upload_queue_family_index;

    VkCommandPool m_graphics_command_pool;
    VkCommandBuffer m_graphics_command_buffer;
    VkCommandPool m_upload_command_pool;
    VkCommandBuffer m_upload_command_buffer;

    VkSemaphore m_upload_queue_submit_semaphore;

    PFN_vkBeginCommandBuffer m_pfn_begin_command_buffer;
    PFN_vkCmdPipelineBarrier m_pfn_cmd_pipeline_barrier;
    PFN_vkCmdCopyBuffer m_pfn_cmd_copy_buffer;
    PFN_vkCmdCopyBufferToImage m_pfn_cmd_copy_buffer_to_image;
    PFN_vkCmdBuildAccelerationStructuresKHR m_pfn_cmd_build_acceleration_structure;
    PFN_vkCmdResetQueryPool m_pfn_cmd_reset_query_pool;
    PFN_vkCmdWriteAccelerationStructuresPropertiesKHR m_pfn_cmd_write_acceleration_structures_properties;
    PFN_vkCmdCopyAccelerationStructureKHR m_pfn_cmd_copy_acceleration_structure;
    PFN_vkEndCommandBuffer m_pfn_end_command_buffer;

public:
    brx_vk_upload_command_buffer();
    void init(bool support_ray_tracing, bool has_dedicated_upload_queue, uint32_t graphics_queue_family_index, uint32_t upload_queue_family_index, PFN_vkGetInstanceProcAddr pfn_get_instance_proc_addr, VkInstance instance, PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks);
    void uninit(PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks);
    ~brx_vk_upload_command_buffer();
    VkCommandPool get_upload_command_pool() const;
    VkCommandBuffer get_upload_command_buffer() const;
    VkCommandPool get_graphics_command_pool() const;
    VkCommandBuffer get_graphics_command_buffer() const;
    VkSemaphore get_upload_queue_submit_semaphore() const;
    void begin() override;
    void upload_from_staging_upload_buffer_to_storage_asset_buffer(brx_storage_asset_buffer *storage_asset_buffer, uint64_t dst_offset, brx_staging_upload_buffer *staging_upload_buffer, uint64_t src_offset, uint32_t src_size) override;
    void upload_from_staging_upload_buffer_to_sampled_asset_image(brx_sampled_asset_image *sampled_asset_image, BRX_SAMPLED_ASSET_IMAGE_FORMAT sampled_asset_image_format, uint32_t sampled_asset_image_width, uint32_t sampled_asset_image_height, uint32_t dst_mip_level, brx_staging_upload_buffer *staging_upload_buffer, uint64_t src_offset, uint32_t src_row_pitch, uint32_t src_row_count) override;
    void build_non_compacted_bottom_level_acceleration_structure_pass_load(uint32_t acceleration_structure_build_input_read_only_buffer_count, brx_acceleration_structure_build_input_read_only_buffer const *const *acceleration_structure_build_input_read_only_buffers) override;
    void build_non_compacted_bottom_level_acceleration_structure(brx_non_compacted_bottom_level_acceleration_structure *non_compacted_bottom_level_acceleration_structure, uint32_t bottom_level_acceleration_structure_geometry_count, BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY const *bottom_level_acceleration_structure_geometries, brx_scratch_buffer *scratch_buffer, brx_compacted_bottom_level_acceleration_structure_size_query_pool *compacted_bottom_level_acceleration_structure_size_query_pool, uint32_t query_index) override;
    void build_non_compacted_bottom_level_acceleration_structure_pass_store(uint32_t acceleration_structure_build_input_read_only_buffer_count, brx_acceleration_structure_build_input_read_only_buffer const *const *acceleration_structure_build_input_read_only_buffers) override;
    void compact_bottom_level_acceleration_structure(brx_compacted_bottom_level_acceleration_structure *destination_compacted_bottom_level_acceleration_structure, brx_non_compacted_bottom_level_acceleration_structure *source_non_compacted_bottom_level_acceleration_structure) override;
    void release(uint32_t storage_asset_buffer_count, brx_storage_asset_buffer const *const *storage_asset_buffers, uint32_t sampled_asset_image_count, brx_sampled_asset_image const *const *sampled_asset_images, uint32_t const *dst_mip_levels, uint32_t compacted_bottom_level_acceleration_structure_count, brx_compacted_bottom_level_acceleration_structure const *const *compacted_bottom_level_acceleration_structures) override;
    void end() override;
};

class brx_vk_fence final : public brx_fence
{
    VkFence m_fence;

public:
    brx_vk_fence(VkFence fence);
    VkFence get_fence() const;
    void steal(VkFence *out_fence);
    ~brx_vk_fence();
};

class brx_vk_descriptor_set_layout final : public brx_descriptor_set_layout
{
    VkDescriptorSetLayout m_descriptor_set_layout;
    uint32_t m_dynamic_uniform_buffer_descriptor_count;
    uint32_t m_storage_buffer_descriptor_count;
    uint32_t m_sampled_image_descriptor_count;
    uint32_t m_sampler_descriptor_count;
    uint32_t m_storage_image_descriptor_count;
    uint32_t m_top_level_acceleration_structure_descriptor_count;

public:
    brx_vk_descriptor_set_layout();
    void init(uint32_t descriptor_set_binding_count, BRX_DESCRIPTOR_SET_LAYOUT_BINDING const *descriptor_set_bindings, PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks);
    void uninit(PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks);
    ~brx_vk_descriptor_set_layout();
    VkDescriptorSetLayout get_descriptor_set_layout() const;
    uint32_t get_dynamic_uniform_buffer_descriptor_count() const;
    uint32_t get_storage_buffer_descriptor_count() const;
    uint32_t get_sampled_image_descriptor_count() const;
    uint32_t get_sampler_descriptor_count() const;
    uint32_t get_storage_image_descriptor_count() const;
    uint32_t get_top_level_acceleration_structure_descriptor_count() const;
};

class brx_vk_pipeline_layout final : public brx_pipeline_layout
{
    VkPipelineLayout m_pipeline_layout;

public:
    brx_vk_pipeline_layout(VkPipelineLayout pipeline_layout);
    VkPipelineLayout get_pipeline_layout() const;
    void steal(VkPipelineLayout *out_pipeline_layout);
    ~brx_vk_pipeline_layout();
};

class brx_vk_descriptor_set final : public brx_descriptor_set
{
    VkDescriptorPool m_descriptor_pool;
    VkDescriptorSet m_descriptor_set;

public:
    brx_vk_descriptor_set();
    void init(brx_descriptor_set_layout const *descriptor_set_layout, PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks);
    void uninit(PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks);
    ~brx_vk_descriptor_set();
    void write_descriptor(PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, uint32_t dst_binding, BRX_DESCRIPTOR_TYPE descriptor_type, uint32_t dst_descriptor_start_index, uint32_t src_descriptor_count, brx_uniform_upload_buffer const *const *src_dynamic_uniform_buffers, uint32_t const *src_dynamic_uniform_buffer_ranges, brx_read_only_storage_buffer const *const *src_read_only_storage_buffers, brx_storage_buffer const *const *src_storage_buffers, brx_sampled_image const *const *src_sampled_images, brx_storage_image const *const *src_storage_images, brx_sampler const *const *src_samplers, brx_top_level_acceleration_structure const *const *src_top_level_acceleration_structures);
    VkDescriptorSet get_descriptor_set() const;
};

class brx_vk_render_pass final : public brx_render_pass
{
    VkRenderPass m_render_pass;

public:
    brx_vk_render_pass(VkRenderPass render_pass);
    VkRenderPass get_render_pass() const;
    void steal(VkRenderPass *out_render_pass);
    ~brx_vk_render_pass();
};

class brx_vk_graphics_pipeline final : public brx_graphics_pipeline
{
    VkPipeline m_pipeline;

public:
    brx_vk_graphics_pipeline();
    void init(PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks, brx_render_pass const *render_pass, brx_pipeline_layout const *pipeline_layout, size_t vertex_shader_module_code_size, void const *vertex_shader_module_code, size_t fragment_shader_module_code_size, void const *fragment_shader_module_code, bool depth_enable, BRX_GRAPHICS_PIPELINE_COMPARE_OPERATION depth_compare_operation);
    void uninit(PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks);
    ~brx_vk_graphics_pipeline();
    VkPipeline get_pipeline() const;
};

class brx_vk_compute_pipeline final : public brx_compute_pipeline
{
    VkPipeline m_pipeline;

public:
    brx_vk_compute_pipeline();
    void init(PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks, brx_pipeline_layout const *pipeline_layout, size_t compute_shader_module_code_size, void const *compute_shader_module_code);
    void uninit(PFN_vkGetDeviceProcAddr pfn_get_device_proc_addr, VkDevice device, VkAllocationCallbacks const *allocation_callbacks);
    ~brx_vk_compute_pipeline();
    VkPipeline get_pipeline() const;
};

class brx_vk_frame_buffer final : public brx_frame_buffer
{
    VkFramebuffer m_frame_buffer;

public:
    brx_vk_frame_buffer(VkFramebuffer frame_buffer);
    VkFramebuffer get_frame_buffer() const;
    void steal(VkFramebuffer *out_frame_buffer);
    ~brx_vk_frame_buffer();
};

class brx_vk_uniform_upload_buffer final : public brx_uniform_upload_buffer
{
    VkBuffer m_buffer;
    VmaAllocation m_allocation;
    void *m_host_memory_range_base;

public:
    brx_vk_uniform_upload_buffer();
    void init(VmaAllocator memory_allocator, VmaPool uniform_upload_buffer_memory_pool, uint32_t size);
    void uninit(VmaAllocator memory_allocator);
    ~brx_vk_uniform_upload_buffer();
    VkBuffer get_buffer() const;
    void *get_host_memory_range_base() const override;
};

class brx_vk_staging_upload_buffer final : public brx_staging_upload_buffer
{
    VkBuffer m_buffer;
    VmaAllocation m_allocation;
    void *m_host_memory_range_base;

public:
    brx_vk_staging_upload_buffer();
    void init(VmaAllocator memory_allocator, VmaPool staging_upload_buffer_memory_pool, uint32_t size);
    void uninit(VmaAllocator memory_allocator);
    VkBuffer get_buffer() const;
    void *get_host_memory_range_base() const override;
    ~brx_vk_staging_upload_buffer();
};

class brx_vk_read_only_storage_buffer : public brx_read_only_storage_buffer
{
public:
    virtual VkBuffer get_buffer() const = 0;
    virtual VkDeviceSize get_size() const = 0;
};

class brx_vk_storage_buffer : public brx_storage_buffer
{
public:
    virtual VkBuffer get_buffer() const = 0;
    virtual VkDeviceSize get_size() const = 0;
};

class brx_vk_acceleration_structure_build_input_read_only_buffer : public brx_acceleration_structure_build_input_read_only_buffer
{
public:
    virtual VkBuffer get_buffer() const = 0;
    virtual VkDeviceAddress get_device_memory_range_base() const = 0;
};

class brx_vk_storage_intermediate_buffer final : public brx_storage_intermediate_buffer, brx_vk_read_only_storage_buffer, brx_vk_storage_buffer, brx_vk_acceleration_structure_build_input_read_only_buffer
{
    VkBuffer m_buffer;
    VmaAllocation m_allocation;
    VkDeviceAddress m_device_memory_range_base;
    VkDeviceSize m_size;

public:
    brx_vk_storage_intermediate_buffer();
    void init(bool support_ray_tracing, VkDevice device, PFN_vkGetBufferDeviceAddressKHR pfn_get_buffer_device_address, VmaAllocator memory_allocator, VmaPool storage_intermediate_buffer_memory_pool, uint32_t size);
    void uninit(VmaAllocator memory_allocator);
    ~brx_vk_storage_intermediate_buffer();

private:
    VkBuffer get_buffer() const override;
    VkDeviceSize get_size() const override;
    VkDeviceAddress get_device_memory_range_base() const override;
    brx_read_only_storage_buffer const *get_read_only_storage_buffer() const override;
    brx_storage_buffer const *get_storage_buffer() const override;
    brx_acceleration_structure_build_input_read_only_buffer const *get_acceleration_structure_build_input_read_only_buffer() const override;
};

class brx_vk_storage_asset_buffer final : public brx_storage_asset_buffer, brx_vk_read_only_storage_buffer, brx_vk_acceleration_structure_build_input_read_only_buffer
{
    VkBuffer m_buffer;
    VmaAllocation m_allocation;
    VkDeviceAddress m_device_memory_range_base;
    VkDeviceSize m_size;

public:
    brx_vk_storage_asset_buffer();
    void init(bool support_ray_tracing, VkDevice device, PFN_vkGetBufferDeviceAddressKHR pfn_get_buffer_device_address, VmaAllocator memory_allocator, VmaPool storage_asset_buffer_memory_pool, uint32_t size);
    void uninit(VmaAllocator memory_allocator);
    ~brx_vk_storage_asset_buffer();

    VkBuffer get_buffer() const override;

private:
    VkDeviceSize get_size() const override;
    VkDeviceAddress get_device_memory_range_base() const override;
    brx_read_only_storage_buffer const *get_read_only_storage_buffer() const override;
    brx_acceleration_structure_build_input_read_only_buffer const *get_acceleration_structure_build_input_read_only_buffer() const override;
};

class brx_vk_sampled_image : public brx_sampled_image
{
public:
    virtual VkImageView get_image_view() const = 0;
};

class brx_vk_color_attachment_image : public brx_color_attachment_image
{
public:
    virtual VkImageView get_image_view() const = 0;
};

class brx_vk_depth_stencil_attachment_image : public brx_depth_stencil_attachment_image
{
public:
    virtual VkImageView get_image_view() const = 0;
};

class brx_vk_storage_image : public brx_storage_image
{
public:
    virtual VkImage get_image() const = 0;
    virtual VkImageView get_image_view() const = 0;
};

class brx_vk_color_attachment_intermediate_image final : public brx_vk_color_attachment_image, brx_vk_sampled_image
{
    VkImage m_image;
    VmaAllocation m_allocation;
    VkImageView m_image_view;

public:
    brx_vk_color_attachment_intermediate_image();
    void init(VkDevice device, PFN_vkCreateImageView pfn_create_image_view, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator, VmaPool color_transient_attachment_image_memory_pool, VmaPool color_attachment_sampled_image_memory_pool, BRX_COLOR_ATTACHMENT_IMAGE_FORMAT color_attachment_image_format, uint32_t width, uint32_t height, bool allow_sampled_image);
    void uninit(VkDevice device, PFN_vkDestroyImageView pfn_destroy_image_view, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator);
    ~brx_vk_color_attachment_intermediate_image();

private:
    VkImageView get_image_view() const override;
    brx_sampled_image const *get_sampled_image() const override;
};

class brx_vk_depth_stencil_attachment_intermediate_image final : public brx_vk_depth_stencil_attachment_image, brx_vk_sampled_image
{
    VkImage m_image;
    VmaAllocation m_allocation;
    VkImageView m_image_view;

public:
    brx_vk_depth_stencil_attachment_intermediate_image();
    void init(VkDevice device, PFN_vkCreateImageView pfn_create_image_view, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator, VmaPool depth_transient_attachment_image_memory_pool, VmaPool depth_attachment_sampled_image_memory_pool, VmaPool depth_stencil_transient_attachment_image_memory_pool, VmaPool depth_stencil_attachment_sampled_image_memory_pool, BRX_DEPTH_STENCIL_ATTACHMENT_IMAGE_FORMAT depth_stencil_attachment_image_format, uint32_t width, uint32_t height, bool allow_sampled_image);
    void uninit(VkDevice device, PFN_vkDestroyImageView pfn_destroy_image_view, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator);
    ~brx_vk_depth_stencil_attachment_intermediate_image();

private:
    VkImageView get_image_view() const override;
    brx_sampled_image const *get_sampled_image() const override;
};

class brx_vk_storage_intermediate_image final : public brx_vk_storage_image, brx_vk_sampled_image
{
    VkImage m_image;
    VmaAllocation m_allocation;
    VkImageView m_image_view;

public:
    brx_vk_storage_intermediate_image();
    void init(VkDevice device, PFN_vkCreateImageView pfn_create_image_view, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator, VmaPool storage_intermediate_image_memory_pool, VkFormat storage_image_format, uint32_t width, uint32_t height, bool allow_sampled_image);
    void uninit(VkDevice device, PFN_vkDestroyImageView pfn_destroy_image_view, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator);
    ~brx_vk_storage_intermediate_image();

private:
    VkImage get_image() const override;
    VkImageView get_image_view() const override;
    brx_sampled_image const *get_sampled_image() const override;
};

class brx_vk_sampled_asset_image final : public brx_sampled_asset_image, brx_vk_sampled_image
{
    VkImage m_image;
    VmaAllocation m_allocation;
    VkImageView m_image_view;
    uint32_t m_mip_levels;

public:
    brx_vk_sampled_asset_image();
    void init(VkDevice device, PFN_vkCreateImageView pfn_create_image_view, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator, VmaPool sampled_asset_image_memory_pool, VkFormat format, uint32_t width, uint32_t height, uint32_t mip_levels);
    void uninit(VkDevice device, PFN_vkDestroyImageView pfn_destroy_image_view, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator);
    ~brx_vk_sampled_asset_image();
    VkImage get_image() const;

private:
    VkImageView get_image_view() const override;
    brx_sampled_image const *get_sampled_image() const override;
    uint32_t get_mip_levels() const override;
};

class brx_vk_sampler final : public brx_sampler
{
    VkSampler m_sampler;

public:
    brx_vk_sampler(VkSampler sampler);
    VkSampler get_sampler() const;
    void steal(VkSampler *out_sampler);
    ~brx_vk_sampler();
};

class brx_vk_surface final : public brx_surface
{
    VkSurfaceKHR m_surface;

public:
    brx_vk_surface();
    void init(
        VkInstance instance,
        VkPhysicalDevice physical_device,
        uint32_t graphics_queue_family_index,
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
        PFN_vkCreateAndroidSurfaceKHR pfn_create_android_surface,
#elif defined(VK_USE_PLATFORM_XCB_KHR)
        PFN_vkCreateXcbSurfaceKHR pfn_create_xcb_surface,
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
        PFN_vkCreateWin32SurfaceKHR pfn_create_win32_surface,
#else
#error Unknown Platform
#endif
        PFN_vkGetPhysicalDeviceSurfaceSupportKHR pfn_get_physical_device_surface_support,
        VkAllocationCallbacks const *allocation_callbacks,
        void *wsi_window);
    void uninit(VkInstance instance, PFN_vkDestroySurfaceKHR pfn_destroy_surface, VkAllocationCallbacks const *allocation_callbacks);
    ~brx_vk_surface();
    VkSurfaceKHR get_surface() const;
};

class brx_vk_swap_chain_image_view final : public brx_vk_color_attachment_image
{
    VkImageView m_image_view;

public:
    brx_vk_swap_chain_image_view();
    void init(VkDevice device, PFN_vkCreateImageView pfn_create_image_view, VkAllocationCallbacks const *allocation_callbacks, VkImage image, VkFormat image_format);
    void uninit(VkDevice device, PFN_vkDestroyImageView pfn_destroy_image_view, VkAllocationCallbacks const *allocation_callbacks);
    ~brx_vk_swap_chain_image_view();

private:
    VkImageView get_image_view() const override;
    brx_sampled_image const *get_sampled_image() const override;
};

class brx_vk_swap_chain final : public brx_swap_chain
{
    VkSwapchainKHR m_swap_chain;
    VkFormat m_image_format;
    uint32_t m_image_width;
    uint32_t m_image_height;
    mcrt_vector<brx_vk_swap_chain_image_view> m_image_views;

public:
    brx_vk_swap_chain();
    void init(VkDevice device, VkPhysicalDevice physical_device, PFN_vkGetPhysicalDeviceSurfaceFormatsKHR pfn_get_physical_device_surface_formats, PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR pfn_get_physical_device_surface_capabilities, PFN_vkGetPhysicalDeviceSurfacePresentModesKHR pfn_get_physical_device_surface_present_modes, PFN_vkCreateSwapchainKHR pfn_create_swap_chain, PFN_vkGetSwapchainImagesKHR pfn_get_swap_chain_images, PFN_vkCreateImageView pfn_create_image_view, VkAllocationCallbacks const *allocation_callbacks, VkSurfaceKHR surface);
    void uninit(VkDevice device, PFN_vkDestroySwapchainKHR pfn_destroy_swapchain, PFN_vkDestroyImageView pfn_destroy_image_view, VkAllocationCallbacks const *allocation_callbacks);
    ~brx_vk_swap_chain();
    VkSwapchainKHR get_swap_chain() const;

private:
    BRX_COLOR_ATTACHMENT_IMAGE_FORMAT get_image_format() const override;
    uint32_t get_image_width() const override;
    uint32_t get_image_height() const override;
    uint32_t get_image_count() const override;
    brx_color_attachment_image const *get_image(uint32_t swap_chain_image_index) const override;
};

class brx_vk_scratch_buffer final : public brx_scratch_buffer
{
    VkBuffer m_buffer;
    VmaAllocation m_allocation;
    VkDeviceAddress m_device_memory_range_base;

public:
    brx_vk_scratch_buffer();
    void init(VkDevice device, PFN_vkGetBufferDeviceAddressKHR pfn_get_buffer_device_address, VmaAllocator memory_allocator, VmaPool scratch_buffer_memory_pool, uint32_t size);
    void uninit(VmaAllocator memory_allocator);
    ~brx_vk_scratch_buffer();
    VkBuffer get_buffer() const;
    VkDeviceAddress get_device_memory_range_base() const;
};

class brx_vk_bottom_level_acceleration_structure : public brx_bottom_level_acceleration_structure
{
public:
    virtual VkDeviceAddress get_device_memory_range_base() const = 0;
};

class brx_vk_intermediate_bottom_level_acceleration_structure final : public brx_intermediate_bottom_level_acceleration_structure, brx_vk_bottom_level_acceleration_structure
{
    VkBuffer m_buffer;
    VmaAllocation m_allocation;
    VkAccelerationStructureKHR m_acceleration_structure;
    VkDeviceAddress m_device_memory_range_base;
    mcrt_vector<BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY> m_bottom_level_acceleration_structure_geometries;

public:
    brx_vk_intermediate_bottom_level_acceleration_structure();
    void init(VkDevice device, PFN_vkCreateAccelerationStructureKHR pfn_create_acceleration_structure, PFN_vkGetAccelerationStructureDeviceAddressKHR pfn_get_acceleration_structure_device_address, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator, VmaPool intermediate_bottom_level_acceleration_structure_memory_pool, uint32_t size);
    void uninit(VkDevice device, PFN_vkDestroyAccelerationStructureKHR pfn_destroy_acceleration_structure, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator);
    ~brx_vk_intermediate_bottom_level_acceleration_structure();
    VkBuffer get_buffer() const;
    VkAccelerationStructureKHR get_acceleration_structure() const;
    void set_bottom_level_acceleration_structure_geometries(uint32_t bottom_level_acceleration_structure_geometry_count, BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY const *wrapped_bottom_level_acceleration_structure_geometries);
    mcrt_vector<BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY> const &get_bottom_level_acceleration_structure_geometries() const;

private:
    VkDeviceAddress get_device_memory_range_base() const override;
    brx_bottom_level_acceleration_structure const *get_bottom_level_acceleration_structure() const override;
};

class brx_vk_non_compacted_bottom_level_acceleration_structure final : public brx_non_compacted_bottom_level_acceleration_structure
{
    VkBuffer m_buffer;
    VmaAllocation m_allocation;
    VkAccelerationStructureKHR m_acceleration_structure;

public:
    brx_vk_non_compacted_bottom_level_acceleration_structure();
    void init(VkDevice device, PFN_vkCreateAccelerationStructureKHR pfn_create_acceleration_structure, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator, VmaPool non_compacted_bottom_level_acceleration_structure_memory_pool, uint32_t size);
    void uninit(VkDevice device, PFN_vkDestroyAccelerationStructureKHR pfn_destroy_acceleration_structure, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator);
    ~brx_vk_non_compacted_bottom_level_acceleration_structure();
    VkBuffer get_buffer() const;
    VkAccelerationStructureKHR get_acceleration_structure() const;
};

class brx_vk_compacted_bottom_level_acceleration_structure_size_query_pool final : public brx_compacted_bottom_level_acceleration_structure_size_query_pool
{
    VkQueryPool m_query_pool;

public:
    brx_vk_compacted_bottom_level_acceleration_structure_size_query_pool();
    void init(VkDevice device, PFN_vkCreateQueryPool pfn_create_query_pool, VkAllocationCallbacks const *allocation_callbacks, uint32_t query_count);
    void uninit(VkDevice device, PFN_vkDestroyQueryPool pfn_destroy_query_pool, VkAllocationCallbacks const *allocation_callbacks);
    ~brx_vk_compacted_bottom_level_acceleration_structure_size_query_pool();
    VkQueryPool get_query_pool() const;
};

class brx_vk_compacted_bottom_level_acceleration_structure final : public brx_compacted_bottom_level_acceleration_structure, brx_vk_bottom_level_acceleration_structure
{
    VkBuffer m_buffer;
    VmaAllocation m_allocation;
    VkAccelerationStructureKHR m_acceleration_structure;
    VkDeviceAddress m_device_memory_range_base;

public:
    brx_vk_compacted_bottom_level_acceleration_structure();
    void init(VkDevice device, PFN_vkCreateAccelerationStructureKHR pfn_create_acceleration_structure, PFN_vkGetAccelerationStructureDeviceAddressKHR pfn_get_acceleration_structure_device_address, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator, VmaPool compacted_bottom_level_acceleration_structure_memory_pool, uint32_t size);
    void uninit(VkDevice device, PFN_vkDestroyAccelerationStructureKHR pfn_destroy_acceleration_structure, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator);
    ~brx_vk_compacted_bottom_level_acceleration_structure();
    VkBuffer get_buffer() const;
    VkAccelerationStructureKHR get_acceleration_structure() const;

private:
    VkDeviceAddress get_device_memory_range_base() const override;
    brx_bottom_level_acceleration_structure const *get_bottom_level_acceleration_structure() const override;
};

class brx_vk_top_level_acceleration_structure_instance_upload_buffer final : public brx_top_level_acceleration_structure_instance_upload_buffer
{
    VkBuffer m_buffer;
    VmaAllocation m_allocation;
    VkDeviceAddress m_device_memory_range_base;
    VkAccelerationStructureInstanceKHR *m_host_memory_range_base;

public:
    brx_vk_top_level_acceleration_structure_instance_upload_buffer();
    void init(VkDevice device, PFN_vkGetBufferDeviceAddressKHR pfn_get_buffer_device_address, VmaAllocator memory_allocator, VmaPool top_level_acceleration_structure_instance_upload_buffer_memory_pool, uint32_t instance_count);
    void uninit(VmaAllocator memory_allocator);
    ~brx_vk_top_level_acceleration_structure_instance_upload_buffer();
    void write_instance(uint32_t instance_index, BRX_TOP_LEVEL_ACCELERATION_STRUCTURE_INSTANCE const *bottom_top_acceleration_structure_instance) override;
    VkBuffer get_buffer() const;
    VkDeviceAddress get_device_memory_range_base() const;
};

class brx_vk_top_level_acceleration_structure final : public brx_top_level_acceleration_structure
{
    VkBuffer m_buffer;
    VmaAllocation m_allocation;
    VkAccelerationStructureKHR m_acceleration_structure;
    uint32_t m_instance_count;

public:
    brx_vk_top_level_acceleration_structure();
    void init(VkDevice device, PFN_vkCreateAccelerationStructureKHR pfn_create_acceleration_structure, PFN_vkGetAccelerationStructureDeviceAddressKHR pfn_get_acceleration_structure_device_address, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator, VmaPool top_level_acceleration_structure_memory_pool, uint32_t size);
    void uninit(VkDevice device, PFN_vkDestroyAccelerationStructureKHR pfn_destroy_acceleration_structure, VkAllocationCallbacks const *allocation_callbacks, VmaAllocator memory_allocator);
    ~brx_vk_top_level_acceleration_structure();
    VkBuffer get_buffer() const;
    VkAccelerationStructureKHR get_acceleration_structure() const;
    void set_instance_count(uint32_t instance_count);
    uint32_t get_instance_count() const;
};

#endif