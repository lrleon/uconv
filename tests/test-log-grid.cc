
# include <string>
# include <sstream>
# include <iostream>

# include <tclap/CmdLine.h>

# include <log-simple-grid.H>

using namespace TCLAP;

Array<double> NdL1Data =
  {
    10.0824, 10.5915, 11.4037, 12.1777, 13.0042, 14.233, 
    15.3251, 16.5003, 18.2083, 20.0945, 21.8145, 23.4882,
    25.4977, 26.7866, 28.3749, 29.8134, 31.0705, 32.1154, 
    32.9255, 34.0382, 34.8956, 35.7764, 36.6807, 37.9164, 
    38.8734, 39.8547, 40.8606, 41.5468, 42.5933, 43.6684, 
    44.7699, 46.2805, 47.4486, 48.2455, 49.4632, 50.7118, 
    51.9918, 53.3032, 54.6458, 56.4816, 58.3813, 60.3395, 
    63.9207, 66.6042, 70.551, 75.3393, 82.4588, 88.7807, 
    97.1805, 107.24, 119.318, 131.671, 145.294, 160.334, 
    179.87, 195.256, 213.707, 233.894, 255.992, 282.496, 
    306.665
  };

Array<double> L1Data =
  {
    2, 2, 2, 2, 2, 2, 1.99414, 1.99414, 1.99414, 1.98828, 
    1.98242, 1.97656, 1.97656, 1.96875, 1.95117, 1.92773,
    1.89844, 1.86719, 1.83203, 1.7832, 1.75391, 1.7168,
    1.67383, 1.63867, 1.60156, 1.56641, 1.53125, 1.5, 1.4707, 
    1.43359, 1.39844, 1.35547, 1.32031, 1.28906, 1.25391, 
    1.2168, 1.18164, 1.14453, 1.11523, 1.0918, 1.06055,
    1.04297,1.01953, 1.00586, 0.994141, 0.994141, 0.994141,
    0.996094, 0.984375, 0.982422, 0.984375, 0.984375, 0.990234,
    0.990234, 0.984375, 0.984375, 0.984375, 0.990234, 0.990234, 
    0.992188, 0.992188
  };

SimpleGrid xygrid = { NdL1Data, L1Data };

template <class Grid>
string test_grid(const Grid & grid, double xstart, double xend, double step)
{
  DynList<double> xvals, yvals;

  for (double x = xstart; x <= xend; x += step)
    {
      xvals.append(x);
      yvals.append(grid(x));
    }

  ostringstream s;
  s << Rvector("x", xvals) << endl
    << Rvector("y", yvals);

  return s.str();
}

CmdLine cmd = { "./test-log-grid", ' ', "0" };

ValueArg<double> xstart = { "s", "start", "x starting value", true, 0,
			    "x starting value", cmd };

ValueArg<double> xend = { "e", "end", "x ending value", true, 0,
			    "x ending value", cmd };

ValueArg<double> step = { "S", "step", "step value", true, 0.1, "step value", cmd };

int main(int argc, char *argv[])
{
  cout << "test" << endl;
  cmd.parse(argc, argv);
  cout << "parsed" << endl;

  cout << Rvector("X", NdL1Data) << endl
       << Rvector("Y", L1Data) << endl
       << test_grid(xygrid, xstart.getValue(), xend.getValue(), step.getValue())
       << endl;
}

