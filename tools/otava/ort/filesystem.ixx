// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.filesystem;

import std.core;

export extern "C" void* fs_path_default_ctor();
export extern "C" void* fs_path_copy_ctor(void* p);
export extern "C" void* fs_path_string_ctor(const char* source);
export extern "C" void fs_path_dtor(void* p);
export extern "C" void fs_path_cat(void* p, void* q);
export extern "C" void fs_path_append(void* p, void* q);
export extern "C" void fs_path_append_str(void* p, const char* x);
export extern "C" void fs_path_append_char(void* p, char x);
export extern "C" void fs_path_clear(void* p);
export extern "C" void fs_path_make_preferred(void* p);
export extern "C" void fs_path_remove_filename(void* p);
export extern "C" void fs_path_replace_filename(void* p, void* q);
export extern "C" void fs_path_replace_extension(void* p, void* q);
export extern "C" void fs_path_remove_extension(void* p);
export extern "C" bool fs_path_equal(void* p, void* q);
export extern "C" void* fs_path_cat2(void* p, void* q);
export extern "C" const char* fs_path_c_str(void* p);
export extern "C" const char* fs_path_generic_str(void* p);
export extern "C" void fs_path_destroy_str(const char* s);
export extern "C" void* fs_path_root_name(void* p);
export extern "C" void* fs_path_root_directory(void* p);
export extern "C" void* fs_path_root_path(void* p);
export extern "C" void* fs_path_relative_path(void* p);
export extern "C" void* fs_path_parent_path(void* p);
export extern "C" void* fs_path_filename(void* p);
export extern "C" void* fs_path_stem(void* p);
export extern "C" void* fs_path_extension(void* p);
export extern "C" bool fs_path_empty(void* p);
export extern "C" bool fs_path_has_root_name(void* p);
export extern "C" bool fs_path_has_root_directory(void* p);
export extern "C" bool fs_path_has_root_path(void* p);
export extern "C" bool fs_path_has_relative_path(void* p);
export extern "C" bool fs_path_has_parent_path(void* p);
export extern "C" bool fs_path_has_filename(void* p);
export extern "C" bool fs_path_has_stem(void* p);
export extern "C" bool fs_path_has_extension(void* p);
export extern "C" bool fs_path_is_absolute(void* p);
export extern "C" bool fs_path_is_relative(void* p);
export extern "C" void* fs_path_absolute(void* p);
export extern "C" void* fs_path_absolute_error(void* p, int* error, char** msg);
export extern "C" void* fs_path_canonical(void* p);
export extern "C" void* fs_path_canonical_error(void* p, int* error, char** msg);
export extern "C" bool fs_copy(void* from, void* to);
export extern "C" void fs_copy_error(void* from, void* to, int* error, char** msg);
export extern "C" bool fs_copy_file(void* from, void* to);
export extern "C" bool fs_copy_file_error(void* from, void* to, int* error, char** msg);
export extern "C" bool fs_create_directories(void* path);
export extern "C" bool fs_create_directories_error(void* path, int* error, char** msg);
export extern "C" void* fs_current_path();
export extern "C" void* fs_current_path_error(int* error, char** msg);
export extern "C" bool fs_set_current_path(void* p);
export extern "C" void fs_set_current_path_error(void* p, int* error, char** msg);
export extern "C" bool fs_equivalent(void* p1, void* p2);
export extern "C" bool fs_equivalent_error(void* p1, void* p2, int* error, char** msg);
export extern "C" bool fs_exists(void* p);
export extern "C" bool fs_exists_error(void* p, int* error, char** msg);
export extern "C" uint64_t fs_file_size(void* p);
export extern "C" uint64_t fs_file_size_error(void* p, int* error, char** msg);
export extern "C" bool fs_is_block_file(void* p);
export extern "C" bool fs_is_block_file_error(void* p, int* error, char** msg);
export extern "C" bool fs_is_character_file(void* p);
export extern "C" bool fs_is_character_file_error(void* p, int* error, char** msg);
export extern "C" bool fs_is_directory(void* p);
export extern "C" bool fs_is_directory_error(void* p, int* error, char** msg);
export extern "C" bool fs_is_empty(void* p);
export extern "C" bool fs_is_empty_error(void* p, int* error, char** msg);
export extern "C" bool fs_is_fifo(void* p);
export extern "C" bool fs_is_fifo_error(void* p, int* error, char** msg);
export extern "C" bool fs_is_other(void* p);
export extern "C" bool fs_is_other_error(void* p, int* error, char** msg);
export extern "C" bool fs_is_regular_file(void* p);
export extern "C" bool fs_is_regular_file_error(void* p, int* error, char** msg);
export extern "C" bool fs_is_socket(void* p);
export extern "C" bool fs_is_socket_error(void* p, int* error, char** msg);
export extern "C" bool fs_is_symlink(void* p);
export extern "C" bool fs_is_symlink_error(void* p, int* error, char** msg);
export extern "C" int64_t fs_last_write_time(void* p);
export extern "C" int64_t fs_last_write_time_error(void* p, int* error, char** msg);
export extern "C" void* fs_relative(void* p);
export extern "C" void* fs_relative_error(void* p, int* error, char** msg);
export extern "C" void* fs_relative_base(void* p, void* base);
export extern "C" void* fs_relative_base_error(void* p, void* base, int* error, char** msg);
export extern "C" bool fs_remove(void* p);
export extern "C" bool fs_remove_error(void* p, int* error, char** msg);
export extern "C" uint64_t fs_remove_all(void* p);
export extern "C" uint64_t fs_remove_all_error(void* p, int* error, char** msg);
export extern "C" void fs_rename(void* from, void* to);
export extern "C" void fs_rename_error(void* from, void* to, int* error, char** msg);
export extern "C" void fs_resize_file(void* p, uint64_t size);
export extern "C" void fs_resize_file_error(void* p, uint64_t size, int* error, char** msg);
