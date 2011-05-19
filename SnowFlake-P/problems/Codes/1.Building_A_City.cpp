//code recheced and verified
#include <iostream>
#include <cstdio>
#include <cassert>

using namespace std;

#define MAXVAL 4611686018427387904LL
#define N 100000
typedef long long ll;

int rate[N] , n ;
ll m ;

ll no_of_floors( ll days )
{
    ll ret = 0 ;

    for ( int i = 0 ; i < n ; i++ )
     ret += days/(ll)rate[i] ;

    return ret;
}

ll time_to_build()
{
    ll l = 0 , r = m*rate[0] , mid ;

	assert(r>0 && r<MAXVAL);
	
    while ( l < r )
    {
        mid = (l+r)/2 ;

        if( no_of_floors(mid) < m )
            l = mid+1 ;
        else
            r = mid ;
    }

    return r ;
}


bool input ()
{
    if ( scanf("%d %lld", &n , &m ) , n == 0 )
        return false;

    for ( int i = 0 ; i < n ; i++ )
        scanf ( "%d" , &rate[i] ) ;

    return true;
}



int main()
{
    while ( input() )
        printf ( "%lld\n" , time_to_build() ) ;
}
