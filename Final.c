/**********************
학번: 20233069
이름: 이예나
[과제#21-프로젝트] 큰 수 계산이 가능한 계산기
개발환경: Visual Studio
실행 운영체제: Windows 11
****************************/

//나눗셈연산이 디버깅중에 갑자기 힙스텍 오류라고 떴습니다.
//계속 해결할 방안을 구했지만 해결하지 못했습니다..
//첨부한 파일을 보시면 힙스텍 오류가 뜰 때 '무시'를 클릭하고 수행하면 결과는 잘 출력이 됩니다.
//이 점 참고해 채점해주시면 감사하겠습니다..

#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isInput(char[]);
void removeZero(char[]);
int compare(char[], char[]);
void add(char[], char[], char[]);
void subtract(char[], char[], char[]);
void multiply(char[], char[], char[]);
void divide(char[], char[], char[]);
void mod(char[], char[], char[]);
void gcd(char[], char[], char[]);

int main()
{
    char a[22] = { '\0' };
    char b[22] = { '\0' };
    int op;

    while (1)
    {
        printf("첫 번째 수를 입력하세요: ");
        scanf("%22s", &a);
        size_t sizeA = strlen(a);
        if (isInput(a) == 0)
        {
            printf("다시 입력하세요\n");
            continue;
        }

        while (1)
        {
            printf("연산을 입력하세요 (0: 종료, 1: 덧셈, 2: 뺄셈, 3: 곱셈, 4: 나눗셈, 5: 최대공약수): ");
            scanf("%d", &op);
            if (op != 0 && op != 1 && op != 2 && op != 3 && op != 4 && op != 5)
            {
                printf("다시 입력하세요\n");
                continue;
            }
            else if (op == 0)
            {
                printf("연산을 종료합니다.");
                break;
            }

            printf("두 번째 수를 입력하세요: ");
            scanf("%22s", &b);
            size_t sizeB = strlen(b);
            if (isInput(b) == 0)
            {
                printf("다시 입력하세요\n");
                continue;
            }

            if (op == 1)
            {
                char* result = (char*)malloc((MAX(sizeA, sizeB) + 2) * sizeof(char));
                printf("%s + %s = ", a, b);
                add(a, b, result);
                printf("%s\n\n", result);
                size_t sizeR = strlen(result);
                strcpy(a, result);
                free(result);
                sizeA = strlen(a);
            }
            else if (op == 2)
            {
                char* result = (char*)malloc((MAX(sizeA, sizeB) + 2) * sizeof(char));
                printf("%s - %s = ", a, b);
                subtract(a, b, result);
                printf(" %s\n\n", result);
                size_t sizeR = strlen(result);
                strcpy(a, result);
                free(result);
                sizeA = strlen(a);
            }
            else if (op == 3)
            {
                char* result = (char*)malloc((sizeA + sizeB + 1) * sizeof(char));
                printf("%s x %s = ", a, b);
                multiply(a, b, result);
                printf("%s\n\n", result);
                size_t sizeR = strlen(result);
                strcpy(a, result);
                free(result);
                sizeA = strlen(a);
            }
            else if (op == 4)
            {
                char* result = (char*)malloc((sizeA - sizeB +1) * sizeof(char));
                printf("%s / %s = ", a, b);
                divide(a, b, result);
                printf("%s\n\n",result);
                size_t sizeR = strlen(result);
                strcpy(a, result);
                sizeA = strlen(a);
                free(result);
            }
            else if (op == 5)
            {
                char* result = (char*)malloc((MAX(sizeA, sizeB)+ 1) * sizeof(char));
                size_t sizeR = strlen(result);
                printf("GCD( %s, %s ) = ", a, b);
                gcd(a, b, result);
                printf("%s\n\n", result);
                sizeR = strlen(result);
                strcpy(a, result);
                sizeA = strlen(a);
                free(result);
            }
        }
        break;
    }
    return 0;
}

//입력받은 수가 정확한 입력인지 확인하는 함수
int isInput(char a[])
{
    char numbers[] = "0123456789";

    int result = 1;
    size_t sizeA = strlen(a);
    for (int i = 0; i < sizeA; i++)
    {
        int x = 0;
        for (int j = 0; j < 10; j++)
        {
            if (a[i] == numbers[j] || a[i] == '\0')
            {
                x = 1;
                break;
            }
        }
        if (!x)
        {
            result = 0;
            break;
        }
    }
    return result;
}

//앞에 0을 없애기 위한 함수
void removeZero(char str[])
{
    size_t size = strlen(str);
    int startIndex = 0;
    while (str[startIndex] == '0')
    {
        startIndex++;
    }

    if (str[startIndex] == '\0')
    {
        str[0] = '0';
        str[1] = '\0';
    }
    else
    {
        for (int i = 0; i <= size - startIndex; i++)
        {
            str[i] = str[i + startIndex];
        }
    }
}

//두 문자열의 크기비교
//a가 b보다 크면 1, 작으면 -1, 같으면 0
int compare(char a[], char b[])
{
    int sizeA = strlen(a);
    int sizeB = strlen(b);
    int result = -1;
    if (sizeA != sizeB)
    {
        return sizeA > sizeB ? 1 : -1;
    }
    
    for (int i = 0; i < sizeA; i++) 
    {
        if (a[i] != b[i]) 
        {
            return a[i] > b[i] ? 1 : -1;
        }
    }

    // 두 문자열이 완전히 동일한 경우
    return 0;
}

void add(char a[], char b[], char result[])
{
    //전 연산에서 a가 음수가 나왔을 경우
    size_t sizeA = strlen(a);
    size_t sizeB = strlen(b);
    if (a[0] == '-')
    {
        memmove(a, a+1, sizeA);
        subtract(a, b, result);
        size_t sizeR = strlen(result);
        memmove(result + 1, result, sizeR+ 1);
        result[0] = '-';
    }
    else
    {
        if (sizeA >= sizeB)
        {
            result[sizeA + 1] = '\0';
            int carry = 0;

            for (int i = 0; i < sizeA; i++)
            {
                //각 자리 수를 정수로 변환
                int digitA = (i < sizeA) ? a[sizeA - 1 - i] - '0' : 0;
                int digitB = (i < sizeB) ? b[sizeB - 1 - i] - '0' : 0;

                int sum = carry + digitA + digitB;
                carry = sum / 10;
                result[sizeA - i] = (sum % 10) + '0';
            }

            if (carry > 0)
            {
                result[0] = carry + '0';
            }
            else
            {
                for (int i = 0; i <= sizeA; i++)
                {
                    result[i] = result[i + 1];
                }
            }
        }
        else
        {
            result[sizeB + 1] = '\0';
            int carry = 0;

            for (int i = 0; i < sizeB; i++)
            {
                int digitA = (i < sizeA) ? a[sizeA - 1 - i] - '0' : 0;
                int digitB = (i < sizeB) ? b[sizeB - 1 - i] - '0' : 0;

                int sum = carry + digitA + digitB;
                carry = sum / 10;
                result[sizeB - i] = (sum % 10) + '0';
            }

            if (carry > 0)
            {
                result[0] = carry + '0';
            }
            else
            {
                for (int i = 0; i <= sizeB; i++)
                {
                    result[i] = result[i + 1];
                }
            }
        }
    }
}

void subtract(char a[], char b[], char result[])
{
    //전 연산에서 a가 음수가 나온 경우
    size_t sizeA = strlen(a);
    size_t sizeB = strlen(b);
    if (a[0] == '-')
    {
        memmove(a, a + 1, sizeA);
        add(a, b, result);
        size_t sizeR = strlen(result);
        memmove(result + 1, result, sizeR);
        result[0] = '-';
    }
    else
    {
        int carry = 0;
        //결과가 무조건 양수
        if (sizeA > sizeB)
        {
            for (int i = 0; i < sizeA + 1; i++)
            {
                result[i] = '0';
            }
            result[sizeA + 1] = '\0';
            for (int i = 0; i < sizeA; i++)
            {
                int digitA = a[sizeA - 1 - i] - '0';
                int digitB = (i < sizeB) ? b[sizeB - 1 - i] - '0' : 0;

                int diff = digitA - digitB + carry;

                if (diff < 0)
                {
                    diff += 10;
                    carry = -1;
                }
                else
                {
                    carry = 0;
                }

                result[sizeA - i] = diff + '0';
            }
            removeZero(result);
        }
        //결과가 양수인지 음수인지 모름
        else if (sizeA == sizeB)
        {
            for (int i = 0; i < sizeA + 1; i++)
            {
                result[i] = '0';
            }
            result[sizeA + 1] = '\0';

            //a == b
            if (strcmp(a, b) == 0)
            {
                removeZero(result);
            }
            //양수
            else if (compare(a, b) == 1)
            {
                for (int i = 0; i < sizeA; i++)
                {
                    int digitA = a[sizeA - 1 - i] - '0';
                    int digitB = (i < sizeB) ? b[sizeB - 1 - i] - '0' : 0;

                    int diff = digitA - digitB + carry;

                    if (diff < 0)
                    {
                        diff += 10;
                        carry = -1;
                    }
                    else
                    {
                        carry = 0;
                    }

                    result[sizeA - i] = diff + '0';
                }
                removeZero(result);
            }
            //음수
            else if (compare(a, b) == -1)
            {
                for (int i = 0; i < sizeA; i++)
                {
                    int digitB = b[sizeB - 1 - i] - '0';
                    int digitA = (i < sizeA) ? a[sizeA - 1 - i] - '0' : 0;

                    int diff = digitB - digitA + carry;

                    if (diff < 0)
                    {
                        diff += 10;
                        carry = -1;
                    }
                    else
                    {
                        carry = 0;
                    }

                    result[sizeB - i] = diff + '0';
                }
                removeZero(result);
                for (int i = sizeA + 1; i >= 0; i--)
                {
                    result[i] = result[i - 1];
                }
                result[0] = '-';
            }
        }
        //결과가 무조건 음수
        else if (sizeA < sizeB)
        {
            //a < b이므로 b에서 a를 빼고 -를 붙여주는 방식
            for (int i = 0; i < sizeB + 1; i++)
            {
                result[i] = '0';
            }
            result[sizeB + 1] = '\0';
            for (int i = 0; i < sizeB; i++)
            {
                int digitB = b[sizeB - 1 - i] - '0';
                int digitA = (i < sizeA) ? a[sizeA - 1 - i] - '0' : 0;

                int diff = digitB - digitA + carry;

                if (diff < 0)
                {
                    diff += 10;
                    carry = -1;
                }
                else
                {
                    carry = 0;
                }

                result[sizeB - i] = diff + '0';
            }
            removeZero(result);
            //한칸씩 밀어주기
            for (int i = sizeB; i >= 0; i--)
            {
                result[i] = result[i - 1];
            }
            result[0] = '-';
        }
    }
    
}

void multiply(char a[], char b[], char result[]) 
{
    int negative = 0;
    //전 연산에서 a가 음수가 나온 경우
    if (a[0] == '-') 
    {
        negative = !negative;
        memmove(a, a + 1, strlen(a));
    }

    size_t sizeA = strlen(a);
    size_t sizeB = strlen(b);
    int* str = (int*)malloc((sizeA + sizeB) * sizeof(int));

    //str 초기화
    for (size_t i = 0; i < sizeA + sizeB; i++) 
    {
        str[i] = 0;
    }
    for (int i = sizeA - 1; i >= 0; i--) 
    {
        for (int j = sizeB - 1; j >= 0; j--) 
        {
            int multi = (a[i] - '0') * (b[j] - '0');
            int sum = multi + str[i + j + 1];

            str[i + j] += sum / 10;
            str[i + j + 1] = sum % 10;
        }
    }

    //결과 문자열
    int startIndex = 0;
    while (startIndex < sizeA + sizeB - 1 && str[startIndex] == 0) 
    {
        startIndex++;
    }

    size_t resultIndex = 0;
    if (negative) 
    {
        result[resultIndex++] = '-';
    }

    for (size_t i = startIndex; i < sizeA + sizeB; i++) 
    {
        result[resultIndex++] = str[i] + '0';
    }
    result[resultIndex] = '\0';
    removeZero(result);
    free(str);
}

void divide(char a[], char b[], char result[])
{
    size_t sizeA = strlen(a);
    //힙스텍 손상 방지
    char* copyA = (char*)malloc(sizeA + 1);

    //전 연산에서 a가 음수가 나온 경우
    int negative = 0;
    if (a[0] == '-')
    {
        negative = 1;
        strcpy(copyA, a + 1);
    }
    else
    {
        strcpy(copyA, a);
    }

    if (compare(copyA, b) == -1)
    {
        strcpy(result, "0");
    }
    else if (compare(copyA, b) == 0)
    {
        if (negative == 0)
        {
            strcpy(result, "1");
        }
        else if (negative == 1)
        {
            strcpy(result, "-1");
        }
    }
    else
    {
        sizeA = strlen(a);
        char* current = (char*)malloc(sizeA + 1);
        char* temp = (char*)malloc(sizeA + 1);
        if (!current || !temp)
        {
            free(copyA);
            free(current);
            free(temp);
            exit(1);
        }
        //초기화해줌
        memset(current, 0, sizeA);
        memset(temp, 0, sizeA);
        current[sizeA] = '\0';
        temp[sizeA] = '\0';

        for (int i = 0; i < sizeA; i++)
        {
            size_t sizeC = strlen(current);
            current[sizeC] = copyA[i];
            current[sizeC + 1] = '\0';

            result[i] = '0';
            while (compare(current, b) >= 0)
            {
                subtract(current, b, temp);
                strcpy(current, temp);
                result[i]++;
            }
        }
        result[sizeA] = '\0';
        removeZero(result);
        int start = 0;
        while (a[start] == '0' && start < sizeA)
        {
            start++;
        }
        if (start > 0)
        {
            memmove(a, a + start, sizeA - start + 1);
        }
        free(current);
        free(temp);

        if (negative == 1)
        {
            memmove(result, result - 1, strlen(result));
            result[0] = '-';
        }
    }
    free(copyA);
}

void mod(char a[], char b[], char result[]) 
{
    int sizeA = strlen(a);
    char* current = (char*)malloc(sizeA + 2);
    char* temp = (char*)malloc(sizeA + 2);

    //current와 temp초기화
    memset(current, 0, sizeA + 2);
    memset(temp, 0, sizeA + 2);

    for (int i = 0; i < sizeA; ++i) 
    {
        size_t sizeC = strlen(current);
        current[sizeC] = a[i];
        current[sizeC + 1] = '\0';

        while (compare(current, b) >= 0) 
        {
            subtract(current, b, temp);
            strcpy(current, temp);
            memset(temp, 0, sizeA + 2);
            //temp를 다시 초기화
        }
    }

    strcpy(result, current);

    free(current);
    free(temp);
}

void gcd(char a[], char b[], char result[])
{
    size_t sizeA = strlen(a) + 1;
    size_t sizeB = strlen(b) + 1;
    char* copyA = (char*)malloc(sizeA + 1);
    char* copyB = (char*)malloc(sizeB + 1);

    //전 연산에서 a가 음수가 나온 경우
    if (a[0] == '-')
    {
        strcpy(copyA, a + 1);
    }
    else
    {
        strcpy(copyA, a);
    }
    strcpy(copyB, b);

    while (strcmp(copyB, "0") != 0)
    {
        char* temp = (char*)malloc(sizeB);
        strcpy(temp, copyB);
        mod(copyA, copyB, copyB);
        strcpy(copyA, temp);
        free(temp);
    }
    strcpy(result, copyA);
    free(copyA);
    free(copyB);
}