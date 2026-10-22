
int proc(int r1, int r2,int r3, int r4,
int r5, int r6,int p7,int p8)
{
    int resp;
    resp = r1+r2+r3+r4+r5+r6+p7+p8;
    return resp;

}

int call_proc()
{
    int v1=1,v2=2,
        v3=3,v4=4,
        v5=5,v6=6,
        v7=7,v8=8;
    return proc(v1,v2,v3,v4,v5,v6,v7,v8);
}
