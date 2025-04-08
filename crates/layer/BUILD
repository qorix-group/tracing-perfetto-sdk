load("@crates//:defs.bzl", "aliases", "all_crate_deps")
load("@rules_rust//rust:defs.bzl", "rust_library")

rust_library(
    name = "layers",
    srcs = glob(["src/**/*.rs"]),
    crate_name = "tracing_perfetto_sdk_layer",
    visibility = ["//visibility:public"],
    crate_features = ["sdk"],
    deps = all_crate_deps(
        normal = True,
    ) + ["//crates/schema:schema"]
)
