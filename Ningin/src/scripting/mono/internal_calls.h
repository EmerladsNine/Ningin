// #pragma once
// #include <iostream>
// #include <string>
// #include <vector>
// #include <cstring>   // For CString equivalents in C++
// #include <stdexcept> // For error handling
// #include <mono/metadata/metadata.h>
// #include <mono/jit/jit.h>
//
// typedef void* MonoMethod;
//
//// Example method collections (you'll replace these with actual ones)
// extern std::vector<std::pair<const char*, MonoMethod>> MATH_METHODS;
// extern std::vector<std::pair<const char*, MonoMethod>> DEBUG_METHODS;
// extern std::vector<std::pair<const char*, MonoMethod>> VECTOR2_METHODS;
// extern std::vector<std::pair<const char*, MonoMethod>> VECTOR3_METHODS;
//
//// Function to add methods
// void add_methods(const std::vector<std::pair<const char*, MonoMethod>>& methods) {
//     for (const auto& [name, method] : methods) {
//         char* cname = strdup(name);  // Create a mutable C-style string
//         if (!cname) {
//             log_error("Failed to allocate memory for method name.");
//             continue;
//         }
//         mono_add_internal_call(cname, method);
//         free(cname);  // Clean up dynamically allocated memory
//     }
// }
//
//// Add all internal calls
// void add_all_internal_calls() {
//     add_methods(MATH_METHODS);
//     add_methods(DEBUG_METHODS);
//     add_methods(VECTOR2_METHODS);
//     add_methods(VECTOR3_METHODS);
// }
//
//// Add a single internal call
// void add_internal_call(const std::string& name, MonoMethod method) {
//     try {
//         mono_add_internal_call(name.c_str(), method);  // Pass C-style string from std::string
//     }
//     catch (const std::exception& e) {
//         log_error(e.what());  // Log error message if any exception occurs
//     }
// }
