load("@crates//:defs.bzl", "aliases", "all_crate_deps")
load("@rules_rust//rust:defs.bzl", "rust_library")



genrule(
    name = "cpp_bindings",
    srcs = [
        "src/lib.rs",
    ],
    outs = [
        "tracing-perfetto-sdk-sys/src/lib.rs.h",
    ],
    cmd = "CXXBRIDGE_CMD=$(location @cxx.rs//:codegen) ./$(location :generate.sh) $(@D) $(SRCS)",
    # Using the cxxbridge binary built by Bazel
    tools = [
        ":generate.sh",
        "@cxx.rs//:codegen",
    ],
)

cc_library(
    name = "perfetto_sdk",
    srcs = ["src/perfetto-bindings.cc", "perfetto-sdk/perfetto.cc"],
    hdrs = ["src/perfetto-bindings.h", "perfetto-sdk/perfetto.h", "tracing-perfetto-sdk-sys/src/lib.rs.h"],
    visibility = ["//visibility:public"],
    deps = [":cpp_bindings", "@cxx.rs//:core"], 
    includes = ["."],

)


rust_library(
    name = "sys",
    srcs = glob(["src/**/*.rs"]),
    crate_name = "tracing_perfetto_sdk_sys",
    visibility = ["//visibility:public"],
    deps = all_crate_deps(
        normal = True,
    ) + [":perfetto_sdk"]
)
