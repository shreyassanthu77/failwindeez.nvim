const std = @import("std");

pub fn build(b: *std.Build) void {
    var lib = b.addStaticLibrary(.{
        .name = "tree-sitter-css",
        .target = b.standardTargetOptions(.{}),
        .optimize = b.standardOptimizeOption(.{}),
    });

    lib.linkLibC();
    lib.addCSourceFiles(.{
        .files = &.{ "src/scanner.c", "src/parser.c" },
        .flags = &.{"-std=c11"},
    });
    lib.addIncludePath(b.path("include"));
    lib.addIncludePath(b.path("src/tree-sitter/"));
    lib.installHeadersDirectory(b.path("include"), ".", .{});

    b.installArtifact(lib);
}
