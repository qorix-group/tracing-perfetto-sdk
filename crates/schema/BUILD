load("@crates//:defs.bzl", "aliases", "all_crate_deps")
load("@rules_rust//rust:defs.bzl", "rust_library", "rust_binary")





rust_library(
    name = "schema",
    srcs = ["src/perfetto.protos.rs"],
    crate_name = "tracing_perfetto_sdk_schema",
    visibility = ["//visibility:public"],
    deps = all_crate_deps(
        normal = True,
    ) 
)
