// .zig
// Program Main Entry Point Script

const std = @import("std");

/// Entry point of the program.
pub fn main() !void {
    var args = std.process.args();
    defer args.deinit();
    const cout = std.io.getStdOut().writer();

    try cout.print("Hello, Dinner!\n", .{});

    // New code here
}
