const std = @import("std");

pub fn build(b: *std.Build) void {
    var lib = b.addStaticLibrary(.{
        .name = "tree-sitter",
        .target = b.standardTargetOptions(.{}),
        .optimize = b.standardOptimizeOption(.{}),
    });

    lib.linkLibC();
    lib.addCSourceFile(.{ .file = b.path("src/lib.c"), .flags = &.{"-std=c11"} });
    lib.addIncludePath(b.path("include"));
    lib.addIncludePath(b.path("src"));

    lib.installHeadersDirectory(b.path("include"), ".", .{});

    b.installArtifact(lib);
}
