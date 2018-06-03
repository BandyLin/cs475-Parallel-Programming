kernel
void
ArrayMult( global const float *dA, global const float *dB, global float *dC )
{
    //1 for multiply, 2 for multiply and add, 3 for reduction
    int i = 3;
	int gid = get_global_id( 0 );
    if (i == 1) {
        dC[gid] = dA[gid] * dB[gid];
    }
    if (i == 2) {
        dC[gid] = dA[gid] * dB[gid] + dc[gid];
    }
    if (i == 3) {
        int numItems = get_local_size(0);
        int tnum = get_local_id(0);
        int wgNum = get_group_id(0);
        prods[tnum] = dA[gid] * dB[gid];
        for (int offset = 1; offset < numItems; offset *= 2) {
            int mask = 2 * offset - 1;
            barrier(CLK_LOCAL_MEM_FENCE);
            if ((tnum & mask) == 0)
                prods[tnum] += prods[tnum + offset];
        }
        barrier(CLK_LOCAL_MEM_FENCE);
        if(tnum == 0)
            dC[wgNum = prods[0]];
    }
}
