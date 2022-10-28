#include "tasks.h"
#include "math.h"
#include "stdio.h"

int
task01 (const char *filename_a, const char *filename_b, const char *s)
{

  int result = 0, flag = 0;
  int i = 0, j = 0;
  FILE *input_a = NULL, *output_b = NULL;
  char curr_str[LEN] = {}, new_s[LEN] = {};

  input_a = fopen (filename_a, "rt");
  if (!input_a)
    {
      fprintf (stderr, "Cannot open file %s\n", filename_a);
      return -1;
    }

  output_b = fopen (filename_b, "wt");
  if (!output_b)
    {
      fclose (input_a);
      fprintf (stderr, "Cannot open file %s\n", filename_b);
      return -1;
    }

  if (s[0] && !s[1])
    new_s[0] = s[0];

  if (s[0] == '\\' && s[1] == '^')
    flag = 1;

  while (s[i])
    {
      if (s[i] == '\\' && (s[i + 1] == '\\' || s[i + 1] == '^'))
        i++;
      new_s[j] = s[i];
      j++;
      i++;
    }
  new_s[j] = '\0';

  while (fgets (curr_str, LEN, input_a))
    is_okay_task1 (curr_str, new_s, flag) ? fprintf (output_b, "%s", curr_str),
        result++                          : 0;

  if (!feof (input_a))
    {
      fclose (input_a);
      fclose (output_b);
      return -2;
    }

  fclose (input_a);
  fclose (output_b);

  return result;
}

int
is_okay_task1 (const char *curr_str, const char *s, int flag)
{
  if (curr_str == NULL)
    return 0;

  if (s == NULL)
    return 0;

  int i = 0, j = 0;

  if (s[0] == '^' && flag == 0)
    {
      for (i = 0; s[i + 1] && s[i + 1] == curr_str[i]; i++)
        if (s[i + 1] == '\n')
          return 1;

      if (!s[i + 1])
        return 1;

      return 0;
    }
  else
    {
      for (i = 0; curr_str[i]; i++)
        {
          if (curr_str[i] == s[0])
            {
              for (j = 1; s[j] && s[j] == curr_str[i + j]; j++)
                if (s[j] == '\n')
                  return 1;

              if (!s[j])
                return 1;

              i++;
            }
        }
    }

  return 0;
}

int
strstr_my (const char *s1, const char *s2)
{
  int i = 0, j = 0;

  if (s2[j] == 0)
    return 0;

  for (i = 0; s1[i]; i++)
    {
      if (s1[i] == s2[0])
        {
          for (j = 0; s1[i + j] && s1[i + j] == s2[j]; j++)
            ;

          if (s2[j] == 0)
            return i;
        }
    }

  return -1;
}
int
strstr_end (const char *s1, const char *s2)
{
  int i = 0, j = 0;

  if (s2[j] == 0)
    return 0;

  for (i = 0; s1[i]; i++)
    {
      if (s1[i] == s2[0])
        {
          for (j = 0; s1[i + j] && s1[i + j] == s2[j]; j++)
            ;

          if (s2[j] == 0 && s1[i + j] == 0)
            {
              return i;
            }
        }
    }

  return -1;
}

int
task02 (const char *filename_a, const char *filename_b, const char *s)
{

  int flag = 0, flag2 = 0, count = 0;
  int i = 0, j = 0;
  FILE *input_a = NULL, *output_b = NULL;
  char curr_str[LEN] = {}, s_buf[LEN] = {};

  input_a = fopen (filename_a, "rt");
  if (!input_a)
    {
      fprintf (stderr, "Cannot open file %s\n", filename_a);
      return -1;
    }

  output_b = fopen (filename_b, "wt");
  if (!output_b)
    {
      fclose (input_a);
      fprintf (stderr, "Cannot open file %s\n", filename_b);
      return -1;
    }

  for (; s[i]; i++, j++)
    {
      flag2 = 0;

      if (s[i] == '\\')
        {
          if (s[i + 1] == '\\' || s[i + 1] == '$')
            {
              i++;
              flag2 = 1;
            }
        }
      s_buf[j] = s[i];
    }

  if (flag2 == 0 && s_buf[j - 1] == '$')
    {
      s_buf[j - 1] = '\0';
      flag = 1;
    }
  else
    s_buf[j] = '\0';

  while (fgets (curr_str, LEN, input_a))
    {
      for (i = 0; curr_str[i]; i++)
        if (curr_str[i] == '\n')
          {
            curr_str[i] = 0;
            break;
          }

      if (flag)
        {
          strstr_end (curr_str, s_buf) >= 0
              ? fprintf (output_b, "%s\n", curr_str),
              count++ : 0;
        }
      else
        {
          strstr_my (curr_str, s_buf) != -1
              ? fprintf (output_b, "%s\n", curr_str),
              count++ : 0;
        }
    }
  if (!feof (input_a))
    {
      fclose (input_a);
      fclose (output_b);
      return -2;
    }

  fclose (input_a);
  fclose (output_b);

  return count;
}

int
task03 (const char *filename_a, const char *filename_b, const char *string)
{
  char buf[LEN] = {}, spaces[3] = { ' ', '\t', 0 };
  FILE *file_a = NULL;
  FILE *file_b = NULL;
  int count = 0;

  file_a = fopen (filename_a, "rt");
  if (!file_a)
    {
      fprintf (stderr, "Cannot open file %s!\n", filename_a);
      return -1;
    }

  file_b = fopen (filename_b, "w");
  if (!file_b)
    {
      fprintf (stderr, "Cannot open file %s\n", filename_b);
      fclose (file_a);
      return -1;
    }

  while (fgets (buf, LEN, file_a))
    {
      if (is_okay_task3 (buf, string, spaces))
        {
          fprintf (file_b, "%s", buf);
          count++;
        }
    }

  if (!feof (file_a))
    {
      fclose (file_a);
      fclose (file_b);
      return -2;
    }

  fclose (file_a);
  fclose (file_b);

  return count;
}

int
is_okay_task3 (const char *curr_str, const char *string, char *spaces)
{
  if (!string[0])
    return 1;
  int i = 0, j = 0;
  char spaces_2[256] = { 0 };

  for (i = 0; spaces[i]; spaces++)
    spaces_2[(unsigned int)spaces[i]] = 1;

  if (!string[2] && string[0] == '\\' && string[1] == '<') // '\<'
    {
      for (i = 0; curr_str[i] && spaces_2[(unsigned int)curr_str[i]]; i++)
        ;
      if (!curr_str[i] || curr_str[i] == '\n')
        return 0;
      else
        return 1;
    }

  if (string[0] == '\\' && string[1] == '<') // '\<*'
    {
      if (string[2] && spaces_2[(unsigned int)string[2]])
        return 0;
      if (curr_str[0] == string[2])
        {
          for (i = 1, j = 3; string[j] && curr_str[i] == string[j]; i++, j++)
            {
              if (string[j + 1] == '\\' && string[j + 2] == '<')
                {
                  if ((spaces_2[(unsigned int)curr_str[i]])
                      && !(spaces_2[(unsigned int)curr_str[i + 1]])
                      && ((curr_str[i + 1] == string[j + 3])
                          || string[j + 3] == 0))
                    {
                      if (!string[j + 3])
                        return 1;
                      i++;
                      j += 3;
                    }
                  else
                    break;
                }
            }
          if (!string[j])
            return 1;
        }
      if (i == 0)
        i++;
      for (; curr_str[i]; i++)
        {
          if ((curr_str[i] == string[2])
              && spaces_2[(unsigned int)curr_str[i - 1]])
            {
              i++;
              for (j = 3; string[j] && string[j] == curr_str[i]; j++, i++)
                {
                  if (string[j + 1] == '\\' && string[j + 2] == '<')
                    {
                      if ((spaces_2[(unsigned int)curr_str[i]])
                          && !(spaces_2[(unsigned int)curr_str[i + 1]])
                          && ((curr_str[i + 1] == string[j + 3])
                              || string[j + 3] == 0))
                        {
                          if (!string[j + 3])
                            return 1;
                          i++;
                          j += 3;
                        }
                      else
                        break;
                    }
                }
              if (!string[j])
                return 1;
              i++;
            }
        }
    }

  for (i = 0; curr_str[i]; i++)
    {
      if (curr_str[i] == string[0])
        {
          for (j = 0;
               string[j] && curr_str[i + j] && string[j] == curr_str[i + j];
               j++)
            {
              if (string[j + 1] && string[j + 2] && string[j + 1] == '\\'
                  && string[j + 2] == '<')
                {
                  if (curr_str[i + j]
                      && (spaces_2[(unsigned int)curr_str[i + j]])
                      && curr_str[i + j + 1]
                      && !(spaces_2[(unsigned int)curr_str[i + j + 1]])
                      && string[j + 3]
                      && (string[j + 3] == 0
                          || (curr_str[i + 1 + j] == string[j + 3])))
                    {
                      if (!string[j + 3])
                        return 1;
                      j += 3;
                    }
                  else
                    break;
                }
            }
          if (!string[j])
            return 1;
        }
    }

  return 0;
}

int
task04 (const char *filename_a, const char *filename_b, const char *string)
{
  char buf[LEN] = {}, spaces[3] = { ' ', '\t', 0 };
  FILE *file_a = NULL;
  FILE *file_b = NULL;
  int count = 0;

  file_a = fopen (filename_a, "rt");
  if (!file_a)
    {
      fprintf (stderr, "Cannot open file %s!\n", filename_a);
      return -1;
    }

  file_b = fopen (filename_b, "w");
  if (!file_b)
    {
      fprintf (stderr, "Cannot open file %s\n", filename_b);
      fclose (file_a);
      return -1;
    }

  while (fgets (buf, LEN, file_a))
    {
      if (is_okay_task4 (buf, string, spaces))
        {
          fprintf (file_b, "%s", buf);
          count++;
        }
    }

  if (!feof (file_a))
    {
      fclose (file_a);
      fclose (file_b);
      return -2;
    }

  fclose (file_a);
  fclose (file_b);

  return count;
}

int
is_okay_task4 (const char *curr_str, const char *string, char *spaces)
{
  if (!string[0])
    return 1;
  int i = 0, j = 0;
  char spaces_2[256] = { 0 };

  for (i = 0; spaces[i]; spaces++)
    spaces_2[(unsigned int)spaces[i]] = 1;

  if (!string[2] && string[0] == '\\' && string[1] == '>') // '\>'
    {
      for (i = 0; curr_str[i] && spaces_2[(unsigned int)curr_str[i]]; i++)
        ;
      if (!curr_str[i] || curr_str[i] == '\n')
        return 0;
      else
        return 1;
    }

  if (string[0] == '\\' && string[1] == '>') // '\>*'
    {
      if (!spaces_2[(unsigned int)string[2]])
        return 0;
      if (curr_str[0] == string[2])
        {
          for (i = 1, j = 3; string[j] && curr_str[i] == string[j]; i++, j++)
            {
              if (string[j + 1] == '\\' && string[j + 2] == '>')
                {
                  if (!spaces_2[(unsigned int)curr_str[i]]
                      && (!curr_str[i] || spaces_2[(unsigned int)curr_str[i]]
                          || curr_str[i] == '\n')
                      && (string[j + 3] == 0
                          || (curr_str[i + 1] == string[j + 3])))
                    {
                      if (!string[j + 3])
                        return 1;
                      i++;
                      j += 3;
                    }
                }
            }
          if (!string[j])
            return 1;
        }
      for (; curr_str[i]; i++)
        {
          if ((curr_str[i] == string[2])
              && !spaces_2[(unsigned int)curr_str[i - 1]])
            {
              i++;
              for (j = 3; string[j] && string[j] == curr_str[i]; j++, i++)
                {
                  if (string[j + 1] == '\\' && string[j + 2] == '>')
                    {
                      if (!spaces_2[(unsigned int)curr_str[i]]
                          && (!curr_str[i]
                              || spaces_2[(unsigned int)curr_str[i]]
                              || curr_str[i] == '\n')
                          && (string[j + 3] == 0
                              || (curr_str[i + 1] == string[j + 3])))
                        if (!string[j + 3])
                          return 1;
                      i++;
                      j += 3;
                    }
                }
              if (!string[j])
                return 1;
              i++;
            }
        }
    }
  for (i = 0; curr_str[i]; i++)
    {
      if (curr_str[i] == string[0])
        {
          for (j = 0;
               string[j] && curr_str[i + j] && string[j] == curr_str[i + j];
               j++)
            {
              if (string[j + 1] == '\\' && string[j + 2] == '>')
                {
                  if (!spaces_2[(unsigned int)curr_str[i + j]]
                      && (!curr_str[i + 1 + j]
                          || spaces_2[(unsigned int)curr_str[i + 1 + j]]
                          || curr_str[i + 1 + j] == '\n')
                      && (string[j + 3] == 0
                          || (curr_str[i + 1 + j] == string[j + 3])))
                    {
                      if (!string[j + 3])
                        return 1;
                      j += 3;
                    }
                }
            }
          if (!string[j])
            return 1;
          i++;
        }
    }
  return 0;
}

int
task05 (const char *filename_a, const char *filename_b, const char *string)
{
  char buf[LEN] = {}, dop_string[LEN] = {};
  FILE *file_a = NULL;
  FILE *file_b = NULL;
  int i = 0, j = 0, count = 0;

  file_a = fopen (filename_a, "rt");
  if (!file_a)
    {
      fprintf (stderr, "Cannot open file %s!\n", filename_a);
      return -1;
    }

  file_b = fopen (filename_b, "w");
  if (!file_b)
    {
      fprintf (stderr, "Cannot open file %s\n", filename_b);
      fclose (file_a);
      return -1;
    }

  for (i = 0, j = 0; string[i]; i++, j++)
    {
      if (string[i + 1] && string[i] == '\\')
        {
          if (string[i + 1] == '.')
            {
              dop_string[j] = '.';
              i++;
            }
          else
            {
              if (string[i + 1] == '\\')
                {
                  dop_string[j] = '\\';
                  i++;
                }
              else
                dop_string[j] = '\\';
            }
        }
      else
        {
          if (string[i] == '.')
            dop_string[j] = '\v';
          else
            dop_string[j] = string[i];
        }
    }
  dop_string[j] = 0;

  while (fgets (buf, LEN, file_a))
    {
      ;
      if (is_okay_task5 (buf, dop_string))
        {
          fprintf (file_b, "%s", buf);
          count++;
        }
    }

  if (!feof (file_a))
    {
      fclose (file_a);
      fclose (file_b);
      return -2;
    }

  fclose (file_a);
  fclose (file_b);
  return (count);
}

int
is_okay_task5 (const char *curr_str, const char *string)
{
  if (!string[0])
    return 1;
  int i = 0, j = 0;

  for (i = 0; curr_str[i]; i++)
    {
      if (curr_str[i] == string[0])
        {
          for (j = 1; string[j] && curr_str[i + j]; j++)
            {
              if (string[j] != curr_str[i + j])
                {
                  if (string[j] == '\v' && curr_str[i + j + 1])
                    continue;
                  else
                    break;
                }
            }
          if (!string[j])
            return 1;
        }
      else
        {
          if (string[0] == '\v')
            {
              for (j = 1; string[j] && string[j] == '\n' && curr_str[i + j];
                   j++)
                ;

              for (j = 1; string[j] && curr_str[i + j]; j++)
                {
                  if (string[j] != curr_str[i + j])
                    {
                      if (string[j] == '\v' && curr_str[i + j + 1])
                        continue;
                      else
                        break;
                    }
                }

              if (!string[j])
                return 1;
            }
        }
    }

  return 0;
}

int
task06 (const char *filename_a, const char *filename_b, const char *string)
{
  char buf[LEN] = {}, dop_string[LEN] = {};
  FILE *file_a = NULL;
  FILE *file_b = NULL;
  int i = 0, j = 0, count = 0;

  file_a = fopen (filename_a, "rt");
  if (!file_a)
    {
      fprintf (stderr, "Cannot open file %s!\n", filename_a);
      return -1;
    }

  file_b = fopen (filename_b, "w");
  if (!file_b)
    {
      fprintf (stderr, "Cannot open file %s\n", filename_b);
      fclose (file_a);
      return -1;
    }

  for (i = 0, j = 0; string[i]; i++, j++)
    {
      if (string[i + 1] && string[i] == '\\')
        {
          if (string[i + 1] == '?')
            {
              dop_string[j] = '?';
              i++;
            }
          else
            {
              if (string[i + 1] == '\\')
                {
                  dop_string[j] = '\\';
                  i++;
                }
              else
                dop_string[j] = '\\';
            }
        }
      else
        {
          if (string[i] == '?')
            dop_string[j] = '\v';
          else
            dop_string[j] = string[i];
        }
    }
  dop_string[j] = 0;

  while (fgets (buf, LEN, file_a))
    {
      if (is_okay_task6 (buf, dop_string))
        {
          fprintf (file_b, "%s", buf);
          count++;
        }
    }

  if (!feof (file_a))
    {
      fclose (file_a);
      fclose (file_b);
      return -2;
    }

  fclose (file_a);
  fclose (file_b);
  return (count);
}

int
is_okay_task6 (const char *curr_str, const char *string)
{
  if (!string[0])
    return 1;
  int i = 0, j = 0, k = 0, l = 0;

  for (l = 0; string[l] && string[l] == '\v'; l++)
    ;
  for (i = 0; curr_str[i]; i++)
    {
      if (curr_str[i] == string[l])
        {
          for (k = i + 1, j = l + 1; string[j] && curr_str[k]; k++, j++)
            {
              if (string[j] != curr_str[k])
                {
                  if (string[j] == '\v')
                    {
                      k--;
                      continue;
                    }
                  else if (string[j + 1] && string[j + 1] == '\v')
                    {
                      k--;
                      continue;
                    }
                  else
                    break;
                }
            }
          if (!string[j])
            return 1;
        }
    }
  return 0;
}

int
task07 (const char *filename_a, const char *filename_b, const char *string)
{
  FILE *file_a = NULL;
  FILE *file_b = NULL;
  char buf[LEN] = { 0 }, spaces[LEN] = { 0 }, dops[LEN] = {};
  char *res = NULL, *buffer = NULL, *second_buffer = NULL, *strstr_ptr = NULL;
  char *words[256] = { 0 };
  int flag = 0, j = 0, k = 0, q = 0, res_len[LEN] = {}, tmp = 0;
  unsigned int spec[LEN] = {};
  int result = 0;

  file_a = fopen (filename_a, "rt");
  if (!file_a)
    {
      fprintf (stderr, "Cannot open file %s!\n", filename_a);
      return -1;
    }
  file_b = fopen (filename_b, "w");
  if (!file_b)
    {
      fprintf (stderr, "Cannot open file %s\n", filename_b);
      fclose (file_a);
      return -1;
    }

  spaces[0] = '\v';
  spaces[1] = 0;

  for (j = 0, k = 0; string[j]; j++, k++)
    {
      if (string[j + 1] && string[j] == '\\')
        {
          if (string[j + 1] == '\\')
            {
              dops[k] = '\\';
              j++;
            }
          else if (string[j + 1] == '+')
            {
              dops[k] = '+';
              j++;
            }
          else
            dops[k] = '\\';
        }
      else if (string[j] == '+')
        {
          while (string[j] && string[j] == '+')
            {
              j++;
              spec[q]++;
            }
          j--;
          q++;
          tmp++;
          dops[k] = '\v';
        }
      else
        dops[k] = string[j];
    }
  dops[k] = 0;

  res = strtok (dops, spaces);
  k = 0;
  if (res)
    {
      words[k] = res;
      res_len[k] = strlen (res);
      k++;
      flag++;
    }

  if (flag > 0)
    {
      do
        {
          res = strtok (NULL, spaces);
          if (res)
            {
              words[k] = res;
              res_len[k] = strlen (res);
              k++;
            }
        }
      while (res);
    }

  while (fgets (buf, LEN, file_a))
    {
      buffer = buf;
      second_buffer = buf;
      j = 0;
      while (words[j])
        {
          if (second_buffer != 0)
            strstr_ptr = strstr (second_buffer, words[j]);
          if (buffer != 0 && strstr_ptr != 0
              && strlen (buffer) - strlen (strstr_ptr) >= spec[j])
            {
              j++;
              buffer = strstr_ptr;
              if (buffer != 0)
                buffer += res_len[j];
            }

          second_buffer = strstr_ptr;
          if (second_buffer != 0)
            second_buffer += res_len[j];
          if (buffer == 0 || buffer[0] == '\n' || strstr_ptr == 0
              || strstr_ptr[0] == '\n')
            break;
        }
      if (spec[j] != 0)
        {
          if (buffer == 0)
            strstr_ptr = 0;
          else if (strlen (buffer) - 2 < spec[j])
            strstr_ptr = 0;
        }

      if (tmp > 0 && words[0] == 0)
        {
          if (strlen (buf) - 1 < spec[0])
            strstr_ptr = 0;
          else
            {
              fprintf (file_b, "%s", buf);
              result++;
            }
        }

      if ((strstr_ptr != 0 && words[j] == 0))
        {
          fputs (buf, file_b);
          result++;
        }
    }

  if (!feof (file_a))
    {
      fclose (file_a);
      fclose (file_b);
      return -2;
    }

  fclose (file_a);
  fclose (file_b);
  return result;
}

int
task08 (const char *filename_a, const char *filename_b, const char *string)
{
  FILE *file_a = NULL;
  FILE *file_b = NULL;
  int res_len[LEN] = {};
  char buf[LEN] = {}, dop_string[LEN] = {}, spaces[LEN] = {},
       *words[256] = { 0 };
  char *strstr_ptr = NULL, *res = NULL, *buffer = NULL;
  int flag = 0, j = 0, k = 0, tmp = 0;
  int result = 0;

  file_a = fopen (filename_a, "rt");
  if (!file_a)
    {
      fprintf (stderr, "Cannot open file %s!\n", filename_a);
      return -1;
    }

  file_b = fopen (filename_b, "w");
  if (!file_b)
    {
      fprintf (stderr, "Cannot open file %s\n", filename_b);
      fclose (file_a);
      return -1;
    }

  spaces[0] = '\v';
  spaces[1] = 0;

  for (j = 0, k = 0; string[j]; j++, k++)
    {
      if (string[j + 1] && string[j] == '\\')
        {
          if (string[j + 1] == '\\')
            {
              dop_string[k] = '\\';
              j++;
            }
          else if (string[j + 1] == '*')
            {
              dop_string[k] = '*';
              j++;
            }
          else
            dop_string[k] = '\\';
        }
      else if (string[j] == '*')
        {
          while (string[j] && string[j] == '*')
            j++;
          j--;
          tmp++;
          dop_string[k] = '\v';
        }
      else
        dop_string[k] = string[j];
    }

  dop_string[k] = 0;

  for (j = 0, k = 0; dop_string[j]; j++)
    {
      if (dop_string[j + 1] && dop_string[j + 1] != '\v')
        {
          dop_string[k] = dop_string[j];
          k++;
        }
    }

  if (dop_string[j - 1] != '\v')
    {
      dop_string[k] = dop_string[j - 1];
      k++;
    }

  dop_string[k] = 0;

  res = strtok (dop_string, spaces);
  k = 0;
  if (res)
    {
      words[k] = res;
      res_len[k] = strlen (res);
      k++;
      flag++;
    }

  if (flag > 0)
    {
      do
        {
          res = strtok (NULL, spaces);
          if (res)
            {
              words[k] = res;
              res_len[k] = strlen (res);
              k++;
            }
        }
      while (res);
    }

  while (fgets (buf, LEN, file_a))
    {
      buffer = buf;
      for (j = 0; words[j]; j++)
        {
          if (buffer != 0)
            strstr_ptr = strstr (buffer, words[j]);
          buffer = strstr_ptr;
          if (buffer != 0)
            buffer += res_len[j];
        }
      if (strstr_ptr != 0 || (tmp > 0 && words[0] == 0))
        {
          fprintf (file_b, "%s", buf);
          result++;
        }
    }

  if (!feof (file_a))
    {
      fclose (file_a);
      fclose (file_b);
      return -2;
    }

  fclose (file_a);
  fclose (file_b);
  return result;
}

int
task09 (const char *filename_a, const char *filename_b, const char *string)
{
  FILE *file_a = NULL;
  FILE *file_b = NULL;
  char buf[LEN] = {}, dop_string[LEN] = {};
  int flag = 0, j = 0, k = 0, result = 0;

  file_a = fopen (filename_a, "rt");
  if (!file_a)
    {
      fprintf (stderr, "Cannot open file %s!\n", filename_a);
      return -1;
    }

  file_b = fopen (filename_b, "w");
  if (!file_b)
    {
      fprintf (stderr, "Cannot open file %s\n", filename_b);
      fclose (file_a);
      return -1;
    }

  for (j = 0, k = 0; string[j]; j++, k++)
    {
      if (string[j + 1] && string[j] == '\\')
        {
          if (string[j + 1] == '\\')
            {
              dop_string[k] = '\\';
              j++;
            }
          else if (string[j + 1] == '[')
            {
              dop_string[k] = '[';
              j++;
            }
          else if (string[j + 1] == ']')
            {
              dop_string[k] = ']';
              j++;
            }
          else
            dop_string[k] = '\\';
        }
      else if (string[j + 4] && string[j] == '[' && string[j + 2] == '-'
               && string[j + 4] == ']')
        {
          dop_string[k] = '\v';
          k++;
          if (string[j + 3] >= string[j + 1])
            {
              dop_string[k] = string[j + 1];
              k++;
              dop_string[k] = string[j + 3];
            }
          else
            {
              dop_string[k] = string[j + 3];
              k++;
              dop_string[k] = string[j + 1];
            }
          j += 4;
        }
      else
        dop_string[k] = string[j];
    }
  dop_string[k] = 0;

  while (fgets (buf, LEN, file_a))
    {
      flag = is_okay_task9 (buf, dop_string);
      if (flag != 0)
        {
          fprintf (file_b, "%s", buf);
          result++;
        }
    }

  if (!feof (file_a))
    {
      fclose (file_a);
      fclose (file_b);
      return -2;
    }

  fclose (file_a);
  fclose (file_b);
  return result;
}

int
is_okay_task9 (const char *string, const char *buf)
{
  int i = 0, j = 0, k = 0;
  for (i = 0; string[i]; i++)
    {
      if (buf[0] == '\v')
        {
          if (string[i] >= buf[1] && string[i] <= buf[2])
            {
              for (j = 3, k = i + 1; buf[j] && string[k]; j++, k++)
                {
                  if (buf[j] != string[k])
                    {
                      if (buf[j] == '\v')
                        {
                          if (!(string[k] >= buf[j + 1]
                                && string[k] <= buf[j + 2]))
                            break;
                          else
                            j += 2;
                        }
                      else
                        break;
                    }
                }
              if (!buf[j])
                return 1;
            }
        }

      if (string[i] == buf[0])
        {
          for (j = 1, k = i + 1; buf[j] && string[k]; j++, k++)
            {
              if (buf[j] != string[k])
                {
                  if (buf[j] == '\v')
                    {
                      if (!(string[k] >= buf[j + 1]
                            && string[k] <= buf[j + 2]))
                        break;
                      else
                        j += 2;
                    }
                  else
                    break;
                }
            }
          if (!buf[j])
            return 1;
        }
    }
  return 0;
}
