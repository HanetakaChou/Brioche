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

#ifndef _BRX_DEVICE_H_
#define _BRX_DEVICE_H_ 1

#include <stddef.h>
#include <stdint.h>
#include "../thirdparty/BRX-Format/include/brx_sampled_asset_image_format.h"

class brx_device;
class brx_graphics_queue;
class brx_upload_queue;
class brx_graphics_command_buffer;
class brx_upload_command_buffer;
class brx_fence;
class brx_descriptor_set_layout;
class brx_pipeline_layout;
class brx_descriptor_set;
class brx_render_pass;
class brx_graphics_pipeline;
class brx_compute_pipeline;
class brx_frame_buffer;
class brx_uniform_upload_buffer;
class brx_staging_upload_buffer;
class brx_read_only_storage_buffer;
class brx_storage_buffer;
class brx_acceleration_structure_build_input_read_only_buffer;
class brx_storage_intermediate_buffer;
class brx_storage_asset_buffer;
class brx_sampled_image;
class brx_color_attachment_image;
class brx_depth_stencil_attachment_image;
class brx_storage_image;
class brx_sampled_asset_image;
class brx_sampler;
class brx_surface;
class brx_swap_chain;
class brx_scratch_buffer;
class brx_bottom_level_acceleration_structure;
class brx_intermediate_bottom_level_acceleration_structure;
class brx_non_compacted_bottom_level_acceleration_structure;
class brx_compacted_bottom_level_acceleration_structure_size_query_pool;
class brx_compacted_bottom_level_acceleration_structure;
class brx_top_level_acceleration_structure_instance_upload_buffer;
class brx_top_level_acceleration_structure;

// (set, binding) => root_parameter_index

enum BRX_DESCRIPTOR_TYPE
{
    BRX_DESCRIPTOR_TYPE_DYNAMIC_UNIFORM_BUFFER = 1,
    BRX_DESCRIPTOR_TYPE_READ_ONLY_STORAGE_BUFFER = 2,
    BRX_DESCRIPTOR_TYPE_STORAGE_BUFFER = 3,
    BRX_DESCRIPTOR_TYPE_SAMPLED_IMAGE = 4,
    BRX_DESCRIPTOR_TYPE_STORAGE_IMAGE = 5,
    BRX_DESCRIPTOR_TYPE_SAMPLER = 6,
    BRX_DESCRIPTOR_TYPE_TOP_LEVEL_ACCELERATION_STRUCTURE = 7
};

enum BRX_COLOR_ATTACHMENT_IMAGE_FORMAT
{
    BRX_COLOR_ATTACHMENT_FORMAT_B8G8R8A8_UNORM = 1,
    BRX_COLOR_ATTACHMENT_FORMAT_R8G8B8A8_UNORM = 2,
    BRX_COLOR_ATTACHMENT_FORMAT_A2B10G10R10_UNORM_PACK32 = 3,
    BRX_COLOR_ATTACHMENT_FORMAT_A2R10G10B10_UNORM_PACK32 = 4,
    BRX_COLOR_ATTACHMENT_FORMAT_R16G16_UNORM = 5,
    BRX_COLOR_ATTACHMENT_FORMAT_R32G32B32A32_UINT = 6
};

enum BRX_DEPTH_STENCIL_ATTACHMENT_IMAGE_FORMAT
{
    BRX_DEPTH_STENCIL_ATTACHMENT_FORMAT_D32_SFLOAT = 1,
    BRX_DEPTH_STENCIL_ATTACHMENT_FORMAT_X8_D24_UNORM_PACK32 = 2,
    BRX_DEPTH_STENCIL_ATTACHMENT_FORMAT_D32_SFLOAT_S8_UINT = 3,
    BRX_DEPTH_STENCIL_ATTACHMENT_FORMAT_D24_UNORM_S8_UINT = 4
};

enum BRX_STORAGE_IMAGE_FORMAT
{
    BRX_STORAGE_IMAGE_FORMAT_R16_SFLOAT = 1,
    BRX_STORAGE_IMAGE_FORMAT_R16G16B16A16_SFLOAT = 2,
    BRX_STORAGE_IMAGE_FORMAT_R32_UINT = 3
};

enum BRX_RENDER_PASS_COLOR_ATTACHMENT_LOAD_OPERATION
{
    BRX_RENDER_PASS_COLOR_ATTACHMENT_LOAD_OPERATION_DONT_CARE = 1,
    BRX_RENDER_PASS_COLOR_ATTACHMENT_LOAD_OPERATION_CLEAR = 2,
};

enum BRX_RENDER_PASS_COLOR_ATTACHMENT_STORE_OPERATION
{
    BRX_RENDER_PASS_COLOR_ATTACHMENT_STORE_OPERATION_DONT_CARE = 1,
    BRX_RENDER_PASS_COLOR_ATTACHMENT_STORE_OPERATION_FLUSH_FOR_SAMPLED_IMAGE = 2,
    BRX_RENDER_PASS_COLOR_ATTACHMENT_STORE_OPERATION_FLUSH_FOR_PRESENT = 3
};

enum BRX_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_LOAD_OPERATION
{
    BRX_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_LOAD_OPERATION_DONT_CARE = 1,
    BRX_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_LOAD_OPERATION_CLEAR = 2
};

enum BRX_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_STORE_OPERATION
{
    BRX_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_STORE_OPERATION_DONT_CARE = 1,
    BRX_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_STORE_OPERATION_FLUSH_FOR_SAMPLED_IMAGE = 2
};

enum BRX_GRAPHICS_PIPELINE_VERTEX_ATTRIBUTE_FORMAT
{
    BRX_GRAPHICS_PIPELINE_VERTEX_ATTRIBUTE_FORMAT_R32G32B32_SFLOAT = 1
};

enum BRX_GRAPHICS_PIPELINE_INDEX_TYPE
{
    BRX_GRAPHICS_PIPELINE_INDEX_TYPE_UINT32 = 1,
    BRX_GRAPHICS_PIPELINE_INDEX_TYPE_UINT16 = 2,
    BRX_GRAPHICS_PIPELINE_INDEX_TYPE_NONE = 3,
};

enum BRX_GRAPHICS_PIPELINE_COMPARE_OPERATION
{
    BRX_GRAPHICS_PIPELINE_COMPARE_OPERATION_GREATER = 1,
    BRX_GRAPHICS_PIPELINE_COMPARE_OPERATION_LESS = 2,
    BRX_GRAPHICS_PIPELINE_COMPARE_OPERATION_ALWAYS = 3
};

enum BRX_COMPUTE_PASS_STORAGE_BUFFER_LOAD_OPERATION
{
    BRX_COMPUTE_PASS_STORAGE_BUFFER_LOAD_OPERATION_DONT_CARE = 1
};

enum BRX_COMPUTE_PASS_STORAGE_IMAGE_LOAD_OPERATION
{
    BRX_COMPUTE_PASS_STORAGE_IMAGE_LOAD_OPERATION_DONT_CARE = 1
};

enum BRX_COMPUTE_PASS_STORAGE_BUFFER_STORE_OPERATION
{
    BRX_COMPUTE_PASS_STORAGE_BUFFER_STORE_OPERATION_FLUSH_FOR_READ_ONLY_STORAGE_BUFFER_AND_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BUFFER = 1
};

enum BRX_COMPUTE_PASS_STORAGE_IMAGE_STORE_OPERATION
{
    BRX_COMPUTE_PASS_STORAGE_IMAGE_STORE_OPERATION_FLUSH_FOR_SAMPLED_IMAGE = 1
};

enum BRX_SAMPLER_FILTER
{
    BRX_SAMPLER_FILTER_NEAREST = 1,
    BRX_SAMPLER_FILTER_LINEAR = 2
};

struct BRX_DESCRIPTOR_SET_LAYOUT_BINDING
{
    uint32_t binding;
    BRX_DESCRIPTOR_TYPE descriptor_type;
    uint32_t descriptor_count;
};

struct BRX_RENDER_PASS_COLOR_ATTACHMENT
{
    BRX_COLOR_ATTACHMENT_IMAGE_FORMAT format;
    BRX_RENDER_PASS_COLOR_ATTACHMENT_LOAD_OPERATION load_operation;
    BRX_RENDER_PASS_COLOR_ATTACHMENT_STORE_OPERATION store_operation;
};

struct BRX_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT
{
    BRX_DEPTH_STENCIL_ATTACHMENT_IMAGE_FORMAT format;
    BRX_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_LOAD_OPERATION load_operation;
    BRX_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_STORE_OPERATION store_operation;
};

struct BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY
{
    bool force_closest_hit;
    BRX_GRAPHICS_PIPELINE_VERTEX_ATTRIBUTE_FORMAT vertex_position_attribute_format;
    uint32_t vertex_position_binding_stride;
    uint32_t vertex_count;
    brx_acceleration_structure_build_input_read_only_buffer const *vertex_position_buffer;
    BRX_GRAPHICS_PIPELINE_INDEX_TYPE index_type;
    uint32_t index_count;
    brx_acceleration_structure_build_input_read_only_buffer const *index_buffer;
};

struct BRX_TOP_LEVEL_ACCELERATION_STRUCTURE_INSTANCE
{
    float transform_matrix[3][4];
    uint32_t instance_id;
    uint8_t instance_mask;
    bool force_closest_hit;
    bool force_any_hit;
    bool disable_back_face_cull;
    bool front_ccw;
    brx_bottom_level_acceleration_structure const *bottom_level_acceleration_structure;
};

// struct brx_xcb_connection_T
// {
//     xcb_connection_t *m_connection;
//     xcb_visualid_t m_visual_id;
// };
extern "C" brx_device *brx_init_vk_device(void *wsi_connection, bool support_ray_tracing);

extern "C" void brx_destroy_vk_device(brx_device *device);

extern "C" brx_device *brx_init_d3d12_device(void *wsi_connection, bool support_ray_tracing);

extern "C" void brx_destroy_d3d12_device(brx_device *device);

class brx_device
{
public:
    virtual brx_graphics_queue *create_graphics_queue() const = 0;
    virtual void destroy_graphics_queue(brx_graphics_queue *graphics_queue) const = 0;
    virtual brx_upload_queue *create_upload_queue() const = 0;
    virtual void destroy_upload_queue(brx_upload_queue *upload_queue) const = 0;
    virtual brx_graphics_command_buffer *create_graphics_command_buffer() const = 0;
    virtual void reset_graphics_command_buffer(brx_graphics_command_buffer *graphics_command_buffer) const = 0;
    virtual void destroy_graphics_command_buffer(brx_graphics_command_buffer *graphics_command_buffer) const = 0;
    virtual brx_upload_command_buffer *create_upload_command_buffer() const = 0;
    virtual void reset_upload_command_buffer(brx_upload_command_buffer *upload_command_buffer) const = 0;
    virtual void destroy_upload_command_buffer(brx_upload_command_buffer *upload_command_buffer) const = 0;
    virtual brx_fence *create_fence(bool signaled) const = 0;
    virtual void wait_for_fence(brx_fence *fence) const = 0;
    virtual void reset_fence(brx_fence *fence) const = 0;
    virtual void destroy_fence(brx_fence *fence) const = 0;
    virtual brx_descriptor_set_layout *create_descriptor_set_layout(uint32_t descriptor_set_binding_count, BRX_DESCRIPTOR_SET_LAYOUT_BINDING const *descriptor_set_bindings) const = 0;
    virtual void destroy_descriptor_set_layout(brx_descriptor_set_layout *descriptor_set_layout) const = 0;
    virtual brx_pipeline_layout *create_pipeline_layout(uint32_t descriptor_set_layout_count, brx_descriptor_set_layout const *const *descriptor_set_layouts) const = 0;
    virtual void destroy_pipeline_layout(brx_pipeline_layout *pipeline_layout) const = 0;
    virtual brx_descriptor_set *create_descriptor_set(brx_descriptor_set_layout const *descriptor_set_layout) = 0;
    virtual void write_descriptor_set(brx_descriptor_set *descriptor_set, uint32_t dst_binding, BRX_DESCRIPTOR_TYPE descriptor_type, uint32_t dst_descriptor_start_index, uint32_t src_descriptor_count, brx_uniform_upload_buffer const *const *src_dynamic_uniform_buffers, uint32_t const *src_dynamic_uniform_buffer_ranges, brx_read_only_storage_buffer const *const *src_read_only_storage_buffers, brx_storage_buffer const *const *src_storage_buffers, brx_sampled_image const *const *src_sampled_images, brx_storage_image const *const *src_storage_images, brx_sampler const *const *src_samplers, brx_top_level_acceleration_structure const *const *src_top_level_acceleration_structures) const = 0;
    virtual void destroy_descriptor_set(brx_descriptor_set *descriptor_set) = 0;
    virtual brx_render_pass *create_render_pass(uint32_t color_attachment_count, BRX_RENDER_PASS_COLOR_ATTACHMENT const *color_attachments, BRX_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT const *depth_stencil_attachment) const = 0;
    virtual void destroy_render_pass(brx_render_pass *render_pass) const = 0;
    virtual brx_graphics_pipeline *create_graphics_pipeline(brx_render_pass const *render_pass, brx_pipeline_layout const *pipeline_layout, size_t vertex_shader_module_code_size, void const *vertex_shader_module_code, size_t fragment_shader_module_code_size, void const *fragment_shader_module_code, bool depth_enable, BRX_GRAPHICS_PIPELINE_COMPARE_OPERATION depth_compare_operation) const = 0;
    virtual void destroy_graphics_pipeline(brx_graphics_pipeline *graphics_pipeline) const = 0;
    virtual brx_compute_pipeline *create_compute_pipeline(brx_pipeline_layout const *pipeline_layout, size_t compute_shader_module_code_size, void const *compute_shader_module_code) const = 0;
    virtual void destroy_compute_pipeline(brx_compute_pipeline *compute_pipeline) const = 0;
    virtual brx_frame_buffer *create_frame_buffer(brx_render_pass const *render_pass, uint32_t width, uint32_t height, uint32_t color_attachment_count, brx_color_attachment_image const *const *color_attachments, brx_depth_stencil_attachment_image const *depth_stencil_attachment) const = 0;
    virtual void destroy_frame_buffer(brx_frame_buffer *frame_buffer) const = 0;
    virtual uint32_t get_uniform_upload_buffer_offset_alignment() const = 0;
    virtual brx_uniform_upload_buffer *create_uniform_upload_buffer(uint32_t size) const = 0;
    virtual void destroy_uniform_upload_buffer(brx_uniform_upload_buffer *uniform_upload_buffer) const = 0;
    virtual uint32_t get_staging_upload_buffer_offset_alignment() const = 0;
    virtual uint32_t get_staging_upload_buffer_row_pitch_alignment() const = 0;
    virtual brx_staging_upload_buffer *create_staging_upload_buffer(uint32_t size) const = 0;
    virtual void destroy_staging_upload_buffer(brx_staging_upload_buffer *staging_upload_buffer) const = 0;
    virtual brx_storage_intermediate_buffer *create_storage_intermediate_buffer(uint32_t size) const = 0;
    virtual void destroy_storage_intermediate_buffer(brx_storage_intermediate_buffer *storage_intermediate_buffer) const = 0;
    virtual brx_storage_asset_buffer *create_storage_asset_buffer(uint32_t size) const = 0;
    virtual void destroy_storage_asset_buffer(brx_storage_asset_buffer *asset_storage_buffer) const = 0;
    virtual brx_color_attachment_image *create_color_attachment_image(BRX_COLOR_ATTACHMENT_IMAGE_FORMAT color_attachment_image_format, uint32_t width, uint32_t height, bool allow_sampled_image) const = 0;
    virtual void destroy_color_attachment_image(brx_color_attachment_image *color_attachment_image) const = 0;
    virtual BRX_DEPTH_STENCIL_ATTACHMENT_IMAGE_FORMAT get_depth_attachment_image_format() const = 0;
    virtual BRX_DEPTH_STENCIL_ATTACHMENT_IMAGE_FORMAT get_depth_stencil_attachment_image_format() const = 0;
    virtual brx_depth_stencil_attachment_image *create_depth_stencil_attachment_image(BRX_DEPTH_STENCIL_ATTACHMENT_IMAGE_FORMAT depth_stencil_attachment_image_format, uint32_t width, uint32_t height, bool allow_sampled_image) const = 0;
    virtual void destroy_depth_stencil_attachment_image(brx_depth_stencil_attachment_image *depth_stencil_attachment_image) const = 0;
    virtual brx_storage_image *create_storage_image(BRX_STORAGE_IMAGE_FORMAT storage_image_format, uint32_t width, uint32_t height, bool allow_sampled_image) const = 0;
    virtual void destroy_storage_image(brx_storage_image *storage_image) const = 0;
    virtual bool is_sampled_asset_image_compression_bc_supported() const = 0;
    virtual bool is_sampled_asset_image_compression_astc_supported() const = 0;
    virtual brx_sampled_asset_image *create_sampled_asset_image(BRX_SAMPLED_ASSET_IMAGE_FORMAT sampled_asset_image_format, uint32_t width, uint32_t height, uint32_t mip_levels) const = 0;
    virtual void destroy_sampled_asset_image(brx_sampled_asset_image *sampled_asset_image) const = 0;
    virtual brx_sampler *create_sampler(BRX_SAMPLER_FILTER filter) const = 0;
    virtual void destroy_sampler(brx_sampler *sampler) const = 0;
    // struct brx_xcb_window_T
    // {
    //     xcb_connection_t *m_connection;
    //     xcb_window_t m_window;
    // };
    virtual brx_surface *create_surface(void *wsi_window) const = 0;
    virtual void destroy_surface(brx_surface *surface) const = 0;
    virtual brx_swap_chain *create_swap_chain(brx_surface *surface) const = 0;
    virtual bool acquire_next_image(brx_graphics_command_buffer *graphics_command_buffer, brx_swap_chain const *swap_chain, uint32_t *out_swap_chain_image_index) const = 0;
    virtual void destroy_swap_chain(brx_swap_chain *swap_chain) const = 0;
    virtual brx_scratch_buffer *create_scratch_buffer(uint32_t size) const = 0;
    virtual void destroy_scratch_buffer(brx_scratch_buffer *scratch_buffer) const = 0;
    virtual void get_intermediate_bottom_level_acceleration_structure_size(uint32_t bottom_level_acceleration_structure_geometry_count, BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY const *bottom_level_acceleration_structure_geometries, uint32_t *intermediate_bottom_level_acceleration_structure_size, uint32_t *build_scratch_size, uint32_t *update_scratch_size) const = 0;
    virtual brx_intermediate_bottom_level_acceleration_structure *create_intermediate_bottom_level_acceleration_structure(uint32_t size) const = 0;
    virtual void destroy_intermediate_bottom_level_acceleration_structure(brx_intermediate_bottom_level_acceleration_structure *intermediate_bottom_level_acceleration_structure) const = 0;
    virtual void get_non_compacted_bottom_level_acceleration_structure_size(uint32_t bottom_level_acceleration_structure_geometry_count, BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY const *bottom_level_acceleration_structure_geometries, uint32_t *non_compacted_bottom_level_acceleration_structure_size, uint32_t *build_scratch_size) const = 0;
    virtual brx_non_compacted_bottom_level_acceleration_structure *create_non_compacted_bottom_level_acceleration_structure(uint32_t size) const = 0;
    virtual void destroy_non_compacted_bottom_level_acceleration_structure(brx_non_compacted_bottom_level_acceleration_structure *non_compacted_bottom_level_acceleration_structure) const = 0;
    virtual brx_compacted_bottom_level_acceleration_structure_size_query_pool *create_compacted_bottom_level_acceleration_structure_size_query_pool(uint32_t query_count) const = 0;
    virtual uint32_t get_compacted_bottom_level_acceleration_structure_size_query_pool_result(brx_compacted_bottom_level_acceleration_structure_size_query_pool const *compacted_bottom_level_acceleration_structure_size_query_pool, uint32_t query_index) const = 0;
    virtual void destroy_compacted_bottom_level_acceleration_structure_size_query_pool(brx_compacted_bottom_level_acceleration_structure_size_query_pool *compacted_bottom_level_acceleration_structure_size_query_pool) const = 0;
    virtual brx_compacted_bottom_level_acceleration_structure *create_compacted_bottom_level_acceleration_structure(uint32_t size) const = 0;
    virtual void destroy_compacted_bottom_level_acceleration_structure(brx_compacted_bottom_level_acceleration_structure *compacted_bottom_level_acceleration_structure) const = 0;
    virtual brx_top_level_acceleration_structure_instance_upload_buffer *create_top_level_acceleration_structure_instance_upload_buffer(uint32_t instance_count) const = 0;
    virtual void destroy_top_level_acceleration_structure_instance_upload_buffer(brx_top_level_acceleration_structure_instance_upload_buffer *top_level_acceleration_structure_instance_upload_buffer) const = 0;
    virtual void get_top_level_acceleration_structure_size(uint32_t top_level_acceleration_structure_instance_count, uint32_t *top_level_acceleration_structure_size, uint32_t *build_scratch_size, uint32_t *update_scratch_size) const = 0;
    virtual brx_top_level_acceleration_structure *create_top_level_acceleration_structure(uint32_t size) const = 0;
    virtual void destroy_top_level_acceleration_structure(brx_top_level_acceleration_structure *top_level_acceleration_structure) const = 0;
};

class brx_graphics_queue
{
public:
    virtual void wait_and_submit(brx_upload_command_buffer const *upload_command_buffer, brx_graphics_command_buffer const *graphics_command_buffer, brx_fence *fence) const = 0;
    virtual bool submit_and_present(brx_graphics_command_buffer *graphics_command_buffer, brx_swap_chain *swap_chain, uint32_t swap_chain_image_index, brx_fence *fence) const = 0;
};

class brx_upload_queue
{
public:
    virtual void submit_and_signal(brx_upload_command_buffer const *upload_command_buffer) const = 0;
};

class brx_graphics_command_buffer
{
public:
    virtual void begin() = 0;
    virtual void acquire(uint32_t storage_asset_buffer_count, brx_storage_asset_buffer const *const *storage_asset_buffers, uint32_t sampled_asset_image_count, brx_sampled_asset_image const *const *sampled_asset_images, uint32_t const *dst_mip_levels, uint32_t compacted_bottom_level_acceleration_structure_count, brx_compacted_bottom_level_acceleration_structure const *const *compacted_bottom_level_acceleration_structures) = 0;
    virtual void begin_debug_utils_label(char const *label_name) = 0;
    virtual void end_debug_utils_label() = 0;
    virtual void begin_render_pass(brx_render_pass const *render_pass, brx_frame_buffer const *frame_buffer, uint32_t width, uint32_t height, uint32_t color_clear_value_count, float const (*color_clear_values)[4], float const *depth_clear_value, uint8_t const *stencil_clear_value) = 0;
    virtual void bind_graphics_pipeline(brx_graphics_pipeline const *graphics_pipeline) = 0;
    virtual void set_view_port(uint32_t width, uint32_t height) = 0;
    virtual void set_scissor(uint32_t width, uint32_t height) = 0;
    virtual void bind_graphics_descriptor_sets(brx_pipeline_layout const *pipeline_layout, uint32_t descriptor_set_count, brx_descriptor_set const *const *descriptor_sets, uint32_t dynamic_offet_count, uint32_t const *dynamic_offsets) = 0;
    virtual void draw(uint32_t vertex_count, uint32_t instance_count) = 0;
    virtual void end_render_pass() = 0;
    virtual void compute_pass_load(uint32_t storage_buffer_count, brx_storage_buffer const *const *storage_buffers, BRX_COMPUTE_PASS_STORAGE_BUFFER_LOAD_OPERATION const *storage_buffer_load_operations, uint32_t storage_image_count, brx_storage_image const *const *storage_images, BRX_COMPUTE_PASS_STORAGE_IMAGE_LOAD_OPERATION const *storage_image_load_operations) = 0;
    virtual void bind_compute_pipeline(brx_compute_pipeline const *compute_pipeline) = 0;
    virtual void bind_compute_descriptor_sets(brx_pipeline_layout const *pipeline_layout, uint32_t descriptor_set_count, brx_descriptor_set const *const *descriptor_sets, uint32_t dynamic_offet_count, uint32_t const *dynamic_offsets) = 0;
    virtual void dispatch(uint32_t group_count_x, uint32_t group_count_y, uint32_t group_count_z) = 0;
    virtual void compute_pass_store(uint32_t storage_buffer_count, brx_storage_buffer const *const *storage_buffers, BRX_COMPUTE_PASS_STORAGE_BUFFER_STORE_OPERATION const *storage_buffer_store_operations, uint32_t storage_image_count, brx_storage_image const *const *storage_images, BRX_COMPUTE_PASS_STORAGE_IMAGE_STORE_OPERATION const *storage_image_store_operations) = 0;
    // NOTE: we do NOT need the "load", since the "acquire" already perform the synchronization
    virtual void build_intermediate_bottom_level_acceleration_structure(brx_intermediate_bottom_level_acceleration_structure *intermediate_bottom_level_acceleration_structure, uint32_t bottom_level_acceleration_structure_geometry_count, BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY const *bottom_level_acceleration_structure_geometries, brx_scratch_buffer *scratch_buffer) = 0;
    virtual void build_intermediate_bottom_level_acceleration_structure_store(uint32_t intermediate_bottom_level_acceleration_structure_count, brx_intermediate_bottom_level_acceleration_structure const *const *intermediate_bottom_level_acceleration_structures) = 0;
    virtual void update_intermediate_bottom_level_acceleration_structure(brx_intermediate_bottom_level_acceleration_structure *intermediate_bottom_level_acceleration_structure, brx_acceleration_structure_build_input_read_only_buffer const *const *bottom_level_acceleration_structure_geometry_vertex_position_buffers, brx_scratch_buffer *scratch_buffer) = 0;
    virtual void update_intermediate_bottom_level_acceleration_structure_store(uint32_t intermediate_bottom_level_acceleration_structure_count, brx_intermediate_bottom_level_acceleration_structure const *const *intermediate_bottom_level_acceleration_structures) = 0;
    virtual void build_top_level_acceleration_structure(brx_top_level_acceleration_structure *top_level_acceleration_structure, uint32_t top_level_acceleration_structure_instance_count, brx_top_level_acceleration_structure_instance_upload_buffer *top_level_acceleration_structure_instance_upload_buffer, brx_scratch_buffer *scratch_buffer) = 0;
    virtual void build_top_level_acceleration_structure_store(brx_top_level_acceleration_structure *top_level_acceleration_structure) = 0;
    virtual void update_top_level_acceleration_structure(brx_top_level_acceleration_structure *top_level_acceleration_structure, brx_top_level_acceleration_structure_instance_upload_buffer *top_level_acceleration_structure_instance_upload_buffer, brx_scratch_buffer *scratch_buffer) = 0;
    virtual void update_top_level_acceleration_structure_store(brx_top_level_acceleration_structure *top_level_acceleration_structure) = 0;
    virtual void end() = 0;
};

class brx_upload_command_buffer
{
public:
    virtual void begin() = 0;
    virtual void upload_from_staging_upload_buffer_to_storage_asset_buffer(brx_storage_asset_buffer *storage_asset_buffer, uint64_t dst_offset, brx_staging_upload_buffer *staging_upload_buffer, uint64_t src_offset, uint32_t src_size) = 0;
    virtual void upload_from_staging_upload_buffer_to_sampled_asset_image(brx_sampled_asset_image *sampled_asset_image, BRX_SAMPLED_ASSET_IMAGE_FORMAT sampled_asset_image_format, uint32_t sampled_asset_image_width, uint32_t sampled_asset_image_height, uint32_t dst_mip_level, brx_staging_upload_buffer *staging_upload_buffer, uint64_t src_offset, uint32_t src_row_pitch, uint32_t src_row_count) = 0;
    // NOTE: We do NOT need any barriers after the "upload" to "store" the buffers or images, since the "load" barriers later will perform the synchronization.
    // TODO: unify the API design // for example, we always use "store" instead of "load" if possible
    virtual void build_non_compacted_bottom_level_acceleration_structure_pass_load(uint32_t acceleration_structure_build_input_read_only_buffer_count, brx_acceleration_structure_build_input_read_only_buffer const *const *acceleration_structure_build_input_read_only_buffers) = 0;
    virtual void build_non_compacted_bottom_level_acceleration_structure(brx_non_compacted_bottom_level_acceleration_structure *non_compacted_bottom_level_acceleration_structure, uint32_t bottom_level_acceleration_structure_geometry_count, BRX_BOTTOM_LEVEL_ACCELERATION_STRUCTURE_GEOMETRY const *bottom_level_acceleration_structure_geometries, brx_scratch_buffer *scratch_buffer, brx_compacted_bottom_level_acceleration_structure_size_query_pool *compacted_bottom_level_acceleration_structure_size_query_pool, uint32_t query_index) = 0;
    // NOTE: we do NOT need the barrier to synchronize the staging non compacted bottom level acceleration structure, since we already use the fence to wait for the GPU completion to retrieve the size of the compacted acceleration structure.
    virtual void build_non_compacted_bottom_level_acceleration_structure_pass_store(uint32_t acceleration_structure_build_input_read_only_buffer_count, brx_acceleration_structure_build_input_read_only_buffer const *const *acceleration_structure_build_input_read_only_buffers) = 0;
    // PBR BOOK V3: ["4.3.4 Compact BVH For Traversal"](https://pbr-book.org/3ed-2018/Primitives_and_Intersection_Acceleration/Bounding_Volume_Hierarchies#CompactBVHForTraversal)
    // PBR BOOK V4: ["7.3.4 Compact BVH for Traversal"](https://pbr-book.org/4ed/Primitives_and_Intersection_Acceleration/Bounding_Volume_Hierarchies#CompactBVHforTraversal)
    virtual void compact_bottom_level_acceleration_structure(brx_compacted_bottom_level_acceleration_structure *destination_compacted_bottom_level_acceleration_structure, brx_non_compacted_bottom_level_acceleration_structure *source_non_compacted_bottom_level_acceleration_structure) = 0;
    virtual void release(uint32_t storage_asset_buffer_count, brx_storage_asset_buffer const *const *storage_asset_buffers, uint32_t sampled_asset_image_count, brx_sampled_asset_image const *const *sampled_asset_images, uint32_t const *dst_mip_levels, uint32_t compacted_bottom_level_acceleration_structure_count, brx_compacted_bottom_level_acceleration_structure const *const *compacted_bottom_level_acceleration_structures) = 0;
    virtual void end() = 0;
};

class brx_fence
{
};

class brx_descriptor_set_layout
{
};

class brx_pipeline_layout
{
};

class brx_descriptor_set
{
};

class brx_render_pass
{
};

class brx_graphics_pipeline
{
};

class brx_compute_pipeline
{
};

class brx_frame_buffer
{
};

class brx_uniform_upload_buffer
{
public:
    virtual void *get_host_memory_range_base() const = 0;
};

class brx_staging_upload_buffer
{
public:
    virtual void *get_host_memory_range_base() const = 0;
};

class brx_read_only_storage_buffer
{
};

class brx_storage_buffer
{
};

class brx_acceleration_structure_build_input_read_only_buffer
{
};

class brx_storage_intermediate_buffer
{
public:
    virtual brx_read_only_storage_buffer const *get_read_only_storage_buffer() const = 0;
    virtual brx_storage_buffer const *get_storage_buffer() const = 0;
    virtual brx_acceleration_structure_build_input_read_only_buffer const *get_acceleration_structure_build_input_read_only_buffer() const = 0;
};

class brx_storage_asset_buffer
{
public:
    virtual brx_read_only_storage_buffer const *get_read_only_storage_buffer() const = 0;
    virtual brx_acceleration_structure_build_input_read_only_buffer const *get_acceleration_structure_build_input_read_only_buffer() const = 0;
};

class brx_sampled_image
{
};

class brx_color_attachment_image
{
public:
    virtual brx_sampled_image const *get_sampled_image() const = 0;
};

class brx_depth_stencil_attachment_image
{
public:
    virtual brx_sampled_image const *get_sampled_image() const = 0;
};

class brx_storage_image
{
public:
    virtual brx_sampled_image const *get_sampled_image() const = 0;
};

class brx_sampled_asset_image
{
public:
    virtual brx_sampled_image const *get_sampled_image() const = 0;
    virtual uint32_t get_mip_levels() const = 0;
};

class brx_sampler
{
};

class brx_surface
{
};

class brx_swap_chain
{
public:
    virtual BRX_COLOR_ATTACHMENT_IMAGE_FORMAT get_image_format() const = 0;
    virtual uint32_t get_image_width() const = 0;
    virtual uint32_t get_image_height() const = 0;
    virtual uint32_t get_image_count() const = 0;
    virtual brx_color_attachment_image const *get_image(uint32_t swap_chain_image_index) const = 0;
};

class brx_scratch_buffer
{
};

class brx_bottom_level_acceleration_structure
{
};

class brx_intermediate_bottom_level_acceleration_structure
{
public:
    virtual brx_bottom_level_acceleration_structure const *get_bottom_level_acceleration_structure() const = 0;
};

class brx_non_compacted_bottom_level_acceleration_structure
{
};

class brx_compacted_bottom_level_acceleration_structure_size_query_pool
{
};

class brx_compacted_bottom_level_acceleration_structure
{
public:
    virtual brx_bottom_level_acceleration_structure const *get_bottom_level_acceleration_structure() const = 0;
};

class brx_top_level_acceleration_structure_instance_upload_buffer
{
public:
    virtual void write_instance(uint32_t instance_index, BRX_TOP_LEVEL_ACCELERATION_STRUCTURE_INSTANCE const *bottom_top_acceleration_structure_instance) = 0;
};

class brx_top_level_acceleration_structure
{
};

#endif