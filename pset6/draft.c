    int n = t->frequency;
    int nl = t->left->frequency;
    int nrc = t->right->symbol;
    int nr = t->right->frequency;
    
    int ml = t->left->left->frequency;
    int mr = t->left->right->frequency;
    int mlc = t->left->left->symbol;
    int mrc = t->left->right->symbol;
  
printf("%i: left %i right %i, %c\n", n, nl, nr, nrc);
printf("%i: left %i, %i right %i, %c\n", nl, ml, mlc, mr, mrc);

printf( "%i %i\n", isLeaf(t->left), isLeaf(t->left->left) );

// create trees
    Tree *h = mktree();
    h->symbol = 'H';
    h->frequency = 2;
    
    Tree *t = mktree();
    t->symbol = 'T';
    t->frequency = 1;
    
    Tree *end = mktree();
    end->symbol = '\n';
    end->frequency = 1;
    
    //plants trees in forest
    plant(f, h);
    plant(f, t);
    plant(f, end);
    
    Tree *t1 = pick(f);
    Tree *t2 = pick(f);
    Tree *te = mktree();
    te->frequency = t1->frequency + t2->frequency;
    te->left = t1; te->right = t2; 
    Tree *t3 = pick(f);
    Tree *teh = mktree();
    teh->frequency = te->frequency + t3->frequency;
    teh->left = te; teh->right = t3;
    plant(f, teh);
