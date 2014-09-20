c
    int q=25,d=10,n=5,p=1,s,ss=0;
    float sf=-1.0,s_int,s_point;
    
    printf ("O hai!");
    while (sf<0){
        printf ("How much change is owed?\n");
        sf=GetFloat();
    }
    
    s_int=roundf(sf);
    s_point=(sf-s_int);
    s=(int) (s_int*100+roundf(s_point*100));
    
    while (q<=s){
        s=s-q;
        ss++;
    }
    while (d<=s){
        s=s-d;
        ss++;
    }
    while (n<=s){
        s=s-n;
        ss++;
    }
    while (p<=s){
        s=s-p;
        ss++;
    }
    
    printf ("%i\n",ss);
    
    return 0;
}
