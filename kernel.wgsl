@group(0)
@binding(0)
var<storage, read_write> mem: array<u32>;

@compute
@workgroup_size(64)
fn main(@builtin(num_workgroups) num_workgroups: vec3<u32>, @builtin(global_invocation_id) global_invocation_id: vec3<u32>) {
    var var_52: u32 = 1u;
    var var_68: u32 = 1u;

    mem[149u] = 0u + var_52; // 0 + 1
    var var_x =  mem[120u];
    mem[120u] = mem[143u] + mem[77u]; // 1 + 1
    mem[149u] = 0u + var_68; // 0 + 1
    mem[150u] = mem[120u] + 1u; // 2 + 1
}

