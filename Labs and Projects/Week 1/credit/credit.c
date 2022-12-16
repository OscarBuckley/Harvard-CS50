#include <cs50.h>
#include <stdio.h>
#include <math.h>
bool validcheck(long cardno, int length)
{

    int oddsum = 0;
    int evensum = 0;
    int totalsum = 0;

    //even number length cc
    for (int i = 2; i <= length; i += 2)
    {

        long temp = 0;

        long div = pow(10, i);

        temp = cardno % div;

        temp = (temp / (div / 10)) * 2;

        if (temp >= 10)
        {

            int temp_1 = temp % 10;
            int temp_10 = temp / 10;
            temp = temp_1 + temp_10;

        }

        evensum += temp;

    }

    //odd number length cc
    for (int i = 1; i <= length; i += 2)
    {

        long temp = 0;

        long div = pow(10, i);

        temp = cardno % div;

        temp = (temp / (div / 10));

        oddsum += temp;

    }

    totalsum = oddsum + evensum;


    if (totalsum % 10 == 0)
    {
        return true;
    }
    else
    {

        return false;
    }

}

int main(void)
{
    int oddsum = 0;
    int evensum = 0;
    int totalsum = 0;
    int length = 0;
    bool valid = false;

    long cardno = get_long("Enter a Number:\n");

    length = log10(cardno) + 1;

    valid = validcheck(cardno, length);

    if (valid == false)
    {

        return printf("INVALID\n");

    }
    else
    {

        int prefix = cardno / (pow(10, length - 2));

        if ((length == 15) && (prefix == 37 || prefix == 34))
        {

            printf("AMEX\n");

        }
        else if (length == 16 && prefix >= 50 && prefix <= 55)
        {

            printf("MASTERCARD\n");

        }
        else if ((length == 16 || length == 13) && (prefix >= 40 && prefix <= 49))
        {

            printf("VISA\n");

        }
        else
        {
            printf("INVALID\n");
        }

        return 0;

    }


}