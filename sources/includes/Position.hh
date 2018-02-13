#ifndef _POSITION_HH_
# define _POSITION_HH_

struct          Position
{
  int  x;
  int  y;
};

struct          Force
{
  double	XPos;
  double	YPos;
  double	XVel;
  double	YVel;
  int		vel;
  int		angl;
};

#endif /* !POSITION_HH_ */
