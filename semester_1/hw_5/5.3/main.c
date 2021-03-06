#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

void infixToPostfix(char *prefixExpression, int prefixExpressionSize);
float counting(char *prefixExpression);

enum token
{
  RIGHTBRACKET,
  LEFTBRACKET,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  ANOTHERTOKEN
};
enum tokensType
{
  NUMBER,
  FUNCTION,
  BRACKET,
  SPACE,
  ANOTHERTYPE
};

int main()
{
  printf("Enter an expression in infix form : ");

  int prefixExpressionSize = 32;
  char *prefixExpression = calloc(prefixExpressionSize, sizeof(char));

  infixToPostfix(prefixExpression, prefixExpressionSize);

  printf("expression = %f\n", counting(prefixExpression));
  free(prefixExpression);
  return 0;
}

int getPriorityOfToken(char token)
{
  switch (token)
  {
  case '(':
    return RIGHTBRACKET;
  case ')':
    return LEFTBRACKET;
  case '+':
    return PLUS;
  case '-':
    return MINUS;
  case '*':
    return MULTIPLY;
  case '/':
    return DIVIDE;
  default:
    return ANOTHERTOKEN;
  }
}

void fatalError(Stack *stack, char *errorMessage)
{
  removeStack(stack);

  perror(errorMessage);
  exit(-1);
}

int typeOfToken(char token)
{
  if (token - '0' >= 0 && token - '9' <= 0)
  {
    return NUMBER;
  }
  else if (token == '+' || token == '-' || token == '*' || token == '/')
  {
    return FUNCTION;
  }
  else if (token == '(' || token == ')')
  {
    return BRACKET;
  }
  else if (token == ' ')
  {
    return SPACE;
  }

  return ANOTHERTYPE;
}

void infixToPostfix(char *prefixExpression, int prefixExpressionSize)
{
  Stack *stack = createStack();
  int numberOfInputTokens = 0;
  char currentToken = '\00';
  while ((currentToken = getchar()) != '\n')
  {
    int typeOfCurrentToken = typeOfToken(currentToken);
    if (typeOfCurrentToken == ANOTHERTYPE)
    {
      free(prefixExpression);
      fatalError(stack, "Incorrect expression\n");
    }
    else if (typeOfCurrentToken == SPACE)
    {
      continue;
    }
    else if (typeOfCurrentToken == NUMBER)
    {
      numberOfInputTokens++;
      prefixExpression[strlen(prefixExpression)] = currentToken;
    }
    else if (typeOfCurrentToken == FUNCTION)
    {
      if (!isEmpty(stack) && typeOfToken(peek(stack)) == FUNCTION)
      {
        free(prefixExpression);
        fatalError(stack, "Incorrect expression\n");  
      }

      numberOfInputTokens++;
      if (isEmpty(stack) || peek(stack) == '(')
      {
        push(currentToken, stack);
      }
      else if (getPriorityOfToken(currentToken) > getPriorityOfToken((char)peek(stack)))
      {
        push((float)currentToken, stack);
      }
      else if (getPriorityOfToken(currentToken) <= getPriorityOfToken((char)peek(stack)))
      {
        while (getPriorityOfToken(currentToken) <= getPriorityOfToken((char)peek(stack)) && (char)peek(stack) != '(')
        {
          prefixExpression[strlen(prefixExpression)] = pop(stack);
          if (isEmpty(stack))
          {
            break;
          }
        }
        push(currentToken, stack);
      }
    }
    else if (typeOfToken(currentToken) == BRACKET)
    {
      numberOfInputTokens++;
      if (currentToken == '(')
      {
        push(currentToken, stack);
      }
      else
      {
        while (peek(stack) != '(')
        {
          prefixExpression[strlen(prefixExpression)] = (char)pop(stack);
        }
        pop(stack);
      }
    }
    if (numberOfInputTokens > prefixExpressionSize - 1)
    {
      prefixExpressionSize *= 2;
      prefixExpression = (char *)realloc(prefixExpression, sizeof(char) * prefixExpressionSize);
    }
  }
  while (!isEmpty(stack))
  {
    prefixExpression[strlen(prefixExpression)] = (char)pop(stack);
  }

  free(stack);
}

float evaluationSimplestExpression(char operator, float operand1, float operand2)
{
  switch (operator)
  {
  case '+':
  {
    return operand1 + operand2;
  }
  case '-':
  {
    return operand1 - operand2;
  }
  case '*':
  {
    return operand1 * operand2;
  }
  case '/':
  {
    return operand1 / operand2;
  }
  }
}

float counting(char *prefixExpression)
{
  Stack *stack = createStack();
  for (int i = 0; i < strlen(prefixExpression); i++)
  {
    char token = prefixExpression[i];
    if (isdigit(token))
    {
      push(token - '0', stack);
    }
    else if (token == '+' || token == '-' || token == '*' || token == '/')
    {
      push(evaluationSimplestExpression(token, pop(stack), pop(stack)), stack);
    }
    else
    {
      free(prefixExpression);
      fatalError(stack, "Unknown token\n");
    }
  }

  if (stackSize(stack) == 1)
  {
    int result = pop(stack);
    free(stack);
    return result;
  }
  else
  {
    fatalError(stack, "Incorrect expression\n");
  }
}