//Nathaniel Quan
//CS407 - Week 7 Lab

#include <cmath>
#include <iostream>
using namespace std;

const int n = 100;
const double PI_OVER_2 = 1.570796327;
const double PI = 2 * 1.570796327;


//Cubic Spline function to calculate b, c, and d coefficients
void cubicSpline(const double x[], const double a[], double b[], double c[], double d[]);

//Trig functions to be defined using cubic splice
double sine(double radians, const double x[], const double a[], const double b[], const double c[], const double d[]);
double cosine(double radians, const double x[], const double a[], const double b[], const double c[], const double d[]);
double tangent(double radians, const double x[], const double a[], const double b[], const double c[], const double d[]);


int main(){
    //The x values of radians from 0 to pi/2
    double x[] =
        {
            0.000000000, 0.015707963, 0.031415927, 0.047123890, 0.062831853, 0.078539816, 0.094247780, 0.109955743, 0.125663706, 0.141371669,
            0.157079633, 0.172787596, 0.188495559, 0.204203522, 0.219911486, 0.235619449, 0.251327412, 0.267035376, 0.282743339, 0.298451302,
            0.314159265, 0.329867229, 0.345575192, 0.361283155, 0.376991118, 0.392699082, 0.408407045, 0.424115008, 0.439822972, 0.455530935,
            0.471238898, 0.486946861, 0.502654825, 0.518362788, 0.534070751, 0.549778714, 0.565486678, 0.581194641, 0.596902604, 0.612610567,
            0.628318531, 0.644026494, 0.659734457, 0.675442421, 0.691150384, 0.706858347, 0.722566310, 0.738274274, 0.753982237, 0.769690200,
            0.785398163, 0.801106127, 0.816814090, 0.832522053, 0.848230016, 0.863937980, 0.879645943, 0.895353906, 0.911061870, 0.926769833,
            0.942477796, 0.958185759, 0.973893723, 0.989601686, 1.005309649, 1.021017612, 1.036725576, 1.052433539, 1.068141502, 1.083849465,
            1.099557429, 1.115265392, 1.130973355, 1.146681319, 1.162389282, 1.178097245, 1.193805208, 1.209513172, 1.225221135, 1.240929098,
            1.256637061, 1.272345025, 1.288052988, 1.303760951, 1.319468915, 1.335176878, 1.350884841, 1.366592804, 1.382300768, 1.398008731,
            1.413716694, 1.429424657, 1.445132621, 1.460840584, 1.476548547, 1.492256510, 1.507964474, 1.523672437, 1.539380400, 1.555088364,
            1.570796327
        };
 
    //The respective sine values of the x values from 0 to pi/2
    double a[] = 
        {
            0.000000000, 0.015707317, 0.031410759, 0.047106451, 0.062790520, 0.078459096, 0.094108313, 0.109734311, 0.125333234, 0.140901232,
            0.156434465, 0.171929100, 0.187381315, 0.202787295, 0.218143241, 0.233445364, 0.248689887, 0.263873050, 0.278991106, 0.294040325,
            0.309016994, 0.323917418, 0.338737920, 0.353474844, 0.368124553, 0.382683432, 0.397147891, 0.411514359, 0.425779292, 0.439939170,
            0.453990500, 0.467929814, 0.481753674, 0.495458668, 0.509041416, 0.522498565, 0.535826795, 0.549022818, 0.562083378, 0.575005252,
            0.587785252, 0.600420225, 0.612907054, 0.625242656, 0.637423990, 0.649448048, 0.661311865, 0.673012514, 0.684547106, 0.695912797,
            0.707106781, 0.718126298, 0.728968627, 0.739631095, 0.750111070, 0.760405966, 0.770513243, 0.780430407, 0.790155012, 0.799684658,
            0.809016994, 0.818149717, 0.827080574, 0.835807361, 0.844327926, 0.852640164, 0.860742027, 0.868631514, 0.876306680, 0.883765630,
            0.891006524, 0.898027576, 0.904827052, 0.911403277, 0.917754626, 0.923879533, 0.929776486, 0.935444031, 0.940880769, 0.946085359,
            0.951056516, 0.955793015, 0.960293686, 0.964557418, 0.968583161, 0.972369920, 0.975916762, 0.979222811, 0.982287251, 0.985109326,
            0.987688341, 0.990023658, 0.992114701, 0.993960955, 0.995561965, 0.996917334, 0.998026728, 0.998889875, 0.999506560, 0.999876632,
            1.000000000,
        };

    //Storage variables needed in cubic spline 
    double b[n+1];
    double c[n+1];
    double d[n+1];

    //Create cubic splines
    cubicSpline(x, a, b, c, d);

    //Set output precision to 9 decimal places, since input values all have 9 decimal places
    cout.setf(ios::fixed);
    cout.precision(9);

    //Get user input
    double input;
    cout << "Domain value of x: ";
    cin >> input;

    cout << endl << endl << "Results:" << endl << endl;
    cout << "sin(" << input << ") = " << sine(input, x, a, b, c, d) << endl;
    cout << "cos(" << input << ") = " << cosine(input, x, a, b, c, d) << endl;
    cout << "tan(" << input << ") = " << tangent(input, x, a, b, c, d) << endl << endl;

    //Pause program at the end
    system("pause");

    return 0;
}


void cubicSpline(const double x[], const double a[], double b[], double c[], double d[])
{
    //For calculation purposes
    double h[n+1];
    double alpha[n+1];
    double l[n+1];
    double mu[n+1];
    double z[n+1];

    //Define the variables
    for (int i = 0; i < n; i++) h[i] = x[i+1] - x[i];
    for (int i = 1; i < n; i++) alpha[i] = 3 * (a[i+1] - a[i]) / h[i] - 3 * (a[i] - a[i-1]) / h[i-1];
    
    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;

    for (int i = 1; i < n; i++){
        l[i] = 2 * (x[i+1] - x[i-1]) - (h[i-1] * mu[i-1]);
        mu[i] = (h[i] / l[i]);
        z[i] = (alpha[i] - h[i-1] * z[i-1]) / l[i];
    }

    l[n] = 1;
    z[n] = 0;
    c[n] = 0;

    // Calculate the coefficients of spline
    for (int i = n-1; i >= 0; i--){
        c[i] = z[i] - mu[i]*c[i+1];
        b[i] = (a[i+1]-a[i])/h[i] - h[i]*(c[i+1]+2*c[i])/3;
        d[i] = (c[i+1] - c[i])/(3*h[i]);
    }
}

double sine(double radians, const double x[], const double a[], const double b[], const double c[], const double d[])
{
    //Sign modifier for final answer if radians is negative
    int initRadianSign = 1;
    int quadrantSign = 1;

    //Check if angle is positive or negative
    if (radians < 0) initRadianSign = -1;                          //Final answer will be negative compared to if absolute value of angle is used
    
    //Use absolute value of angle
    radians = fabs(radians);

    //Reduce angle given to be within 2*pi
    while (radians > 4 * PI_OVER_2) radians -= (4*PI_OVER_2);

    //The answer will be negative when pi <= x <= 2pi
    if (radians > PI) quadrantSign = -1;

    //Reduce angle to be within 0 and pi because the rest of the sine function is just a repetition of these two quadrants
    if (radians > PI) radians -= PI;

    //Reduce angle given to be within pi/2 since cubic spline is only defined from 0 to pi/2
    if (radians > PI_OVER_2) radians = PI_OVER_2 - (radians - PI_OVER_2);    

    //Find the spline
    int s;                                      //Index of spline
    for (s = 0; s < n; s++)
        if (radians >= x[s] && radians <= x[s+1]) break;

    double diff = radians - x[s];
    double answer = a[s] + b[s]*diff + c[s]*diff*diff + d[s]*diff*diff*diff;

    //Add back in the effects of the signs
    answer = initRadianSign * quadrantSign * answer;

    return answer;
    //return 0.0;
}

double cosine(double radians, const double x[], const double a[], const double b[], const double c[], const double d[])
{
    //Cosine(x) = Sine(x + pi/2)
    radians = radians + PI_OVER_2;
    return sine(radians, x, a, b, c, d);
}

double tangent(double radians, const double x[], const double a[], const double b[], const double c[], const double d[])
{
    //Tangent = Sine / Cosine
    double sin = sine(radians, x, a, b, c, d);
    double cos = cosine(radians, x, a, b, c, d);

    return sin/cos;
}