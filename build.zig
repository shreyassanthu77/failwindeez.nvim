const std = @import("std");

fn getBinDir(allocator: std.mem.Allocator, optimize: std.builtin.OptimizeMode, name: []const u8) []const u8 {
    const opt = switch (optimize) {
        .Debug => "debug",
        .ReleaseSafe => "release-safe",
        .ReleaseFast => "release-fast",
        .ReleaseSmall => "release-small",
    };

    return std.mem.join(allocator, "-", &.{ name, opt }) catch |err| {
        std.debug.panic("Failed to join strings: {}\n", .{err});
    };
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const tree_sitter = b.dependency("tree-sitter", .{
        .target = target,
        .optimize = optimize,
    });
    const tree_sitter_css = b.dependency("tree-sitter-css", .{
        .target = target,
        .optimize = optimize,
    });

    const failwindeez = b.addExecutable(.{
        .name = "failwindeez",
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });

    failwindeez.addCSourceFiles(.{
        .files = &.{
            "main.c",
            "src/result.c",
            "src/strings.c",
            "src/fs.c",
        },
        .flags = &.{
            "-std=c23",
        },
    });
    failwindeez.addIncludePath(b.path("include/"));
    failwindeez.linkLibrary(tree_sitter.artifact("tree-sitter"));
    failwindeez.linkLibrary(tree_sitter_css.artifact("tree-sitter-css"));

    const bin_dir = getBinDir(b.allocator, optimize, failwindeez.name);

    const exe = b.addInstallArtifact(failwindeez, .{
        .dest_dir = .{
            .override = .{
                .custom = bin_dir,
            },
        },
    });
    b.getInstallStep().dependOn(&exe.step);
    const run_exe = b.addRunArtifact(exe.artifact);
    if (b.args) |args| {
        run_exe.addArgs(args);
    }

    const run_step = b.step("run", "Run the executable");
    run_step.dependOn(&run_exe.step);
}
