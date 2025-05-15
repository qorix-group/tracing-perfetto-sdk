use std::{env, path};

fn main() -> anyhow::Result<()> {
    let manifest_dir = env::var_os("CARGO_MANIFEST_DIR")
        .expect("CARGO_MANIFEST_DIR to always be set by `cargo build`");
    let manifest_dir = path::Path::new(&manifest_dir);

    let mut builder = cc::Build::new();

    let c = env::var_os("CXX");

    if c.as_ref()
        .unwrap_or(&"".into())
        .to_str()
        .unwrap()
        .contains("llvm")
    {
        println!("cargo:rustc-link-arg=-lstdc++");
        println!("cargo:rustc-link-lib=stdc++");
    }

    if c.is_some() {
        builder.compiler(c.unwrap());
    }

    // Bazel does not allow code generation within its sandbox, so we need to compile the pre-generated
    // code instead. Make sure to re-generate the lib.rs.* everytime the lib.rs is modified.
    // Note that the generated code must be compiled here together with the rest of the native
    // files lest some of the generated symbols will be stripped from the final crate library
    builder
        .file("tracing-perfetto-sdk-sys/src/lib.rs.cc")
        .file("perfetto-sdk/perfetto.cc")
        .file("src/perfetto-bindings.cc")
        .std("c++17")
        .include(manifest_dir)
        .include(manifest_dir.join("src"))
        .flag_if_supported("-Wno-redundant-move")
        .flag_if_supported("-Wno-deprecated-declarations")
        .compile("tracing-perfetto-sdk");

    println!("cargo:rerun-if-changed=tracing-perfetto-sdk-sys/lib.rs.cc");
    println!("cargo:rerun-if-changed=src/perfetto-bindings.h");
    println!("cargo:rerun-if-changed=src/perfetto-bindings.cc");
    println!("cargo:rerun-if-changed=perfetto-sdk/perfetto.h");
    println!("cargo:rerun-if-changed=perfetto-sdk/perfetto.cc");

    Ok(())
}
