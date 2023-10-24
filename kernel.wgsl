@group(0)
@binding(0)
var<storage, read_write> mem: array<u32>;

@compute
@workgroup_size(1)
fn main() {
    mem[0u] = 1u;
    var a = mem[1u];
    mem[1u] = 2u;
    mem[0u] = 1u;
    mem[2u] = mem[1u]; // 2
}

