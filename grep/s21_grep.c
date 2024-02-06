#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char pattern[1024] = "\0";
  flag opts = {0};

  parser(argc, argv, &opts, pattern);
  search(argc, argv, &opts, pattern);
  return 0;
}
/**
 * @brief Расстановка флагов в структуре
 *
 * @param argc количество аргументов командной строки
 * @param argv массив указателей на символы аргументов командной строки
 * @param f указатель на структуру флагов
 * @param pattern указатель на массив символов с шаблоном поиска
 */
void parser(int argc, char *argv[], flag *f, char *pattern) {
  int flag;
  while ((flag = getopt_long(argc, argv, "e:ivclnhsf:o", 0, 0)) != -1) {
    switch (flag) {
      case 'e':
        f->e = 1;
        grep_e(pattern, optarg);
        break;
      case 'i':
        f->i = 1;
        break;
      case 'v':
        f->v = 1;
        break;
      case 'c':
        f->c = 1;
        break;
      case 'l':
        f->l = 1;
        break;
      case 'n':
        f->n = 1;
        break;
      case 'h':
        f->h = 1;
        break;
      case 's':
        f->s = 1;
        break;
      case 'f':
        f->f = 1;
        grep_f(pattern, optarg);
        break;
      case 'o':
        f->o = 1;
        break;
      default:
        fprintf(stderr, "invalid option");
        exit(1);
        break;
    }
    flags_browse(f);
  }
}
/**
 * @brief Функция открытия файла, компиляции регулярного выражения включающая
 * отработку флагов
 *
 * @param argc количество аргументов командной строки
 * @param argv массив указателей на символы аргументов командной строки
 * @param f указатель на структуру флагов
 * @param pattern указатель на массив символов с шаблоном поиска
 */
void search(int argc, char *argv[], flag *f, char *pattern) {
  FILE *fp = NULL;
  char str[size] = {0};
  regex_t regex;
  int cflags = REG_EXTENDED;
  if (!(f->e || f->f) && argv[optind]) {
    strcpy(pattern, argv[optind]);
    optind++;
  }
  if (f->i == 1) {
    cflags = REG_ICASE;
  }
  int file_count = 1;
  if ((argc - optind) > 1) {
    file_count++;
  }
  for (int i = optind; i < argc; ++i) {
    if (argv[i][0] != '-') {
      if ((fp = fopen(argv[i], "r")) == NULL) {
        if (f->s != 1) {
          fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
          continue;
        }
      }
      if (fp != NULL) {
        regcomp(&regex, pattern, cflags);
        flags(regex, f, str, fp, file_count, argv[i]);
      } else {
        if (f->s != 1) {
          fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
        }
      }
    }
    if (fp != NULL) {
      regfree(&regex);
      fclose(fp);
    }
  }
}
/**
 * @brief Отработка флагов
 *
 * @param regex скомпилированное регулярное выражение
 * @param f указатель на структуру флагов
 * @param str массив для записи строки из файла
 * @param fp указатель на файл для поиска
 * @param file_count количество файлов
 * @param filename имя файла
 */
void flags(regex_t regex, flag *f, char *str, FILE *fp, int file_count,
           char *filename) {
  regmatch_t pmatch[1];
  int count = 0;
  int line = 0;
  while (fgets(str, size - 1, fp) != NULL) {
    int match = 0;
    count++;
    int success = 0;
    char *begin_str = str;
    while ((success = regexec(&regex, begin_str, 1, pmatch, 0)) == 0) {
      if ((file_count > 1) && f->h != 1 && f->l != 1 && f->c != 1 &&
          f->o == 1) {
        printf("%s:", filename);
      }
      if (f->n == 1 && f->o == 1) {
        printf("%d:", count);
      }
      if (f->o == 1) {
        for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
          printf("%c", begin_str[i]);
        }
        printf("\n");
      }
      match += 1;
      begin_str += pmatch[0].rm_eo;
    }
    if (f->v == 1) {
      match = !match;
    }
    if (f->o != 1) {
      if (match && (file_count > 1) && f->h != 1 && f->l != 1 && f->c != 1) {
        printf("%s:", filename);
      }
      if (match && f->n == 1) {
        printf("%d:", count);
      }
    }
    if (match && f->c != 1 && f->l != 1 && f->o != 1) {
      if (strchr(str, '\n') == NULL) {
        strcat(str, "\n");
      }
      printf("%s", str);
    }
    line += !!match;
  }
  print(f, line, file_count, filename);
}
/**
 * @brief Расстановка не работающих вместе флагов
 *
 * @param f указатель на структуру флагов
 */
void flags_browse(flag *f) {
  if (f->l == 1) {
    f->n = 0;
    f->o = 0;
  }
  if (f->c == 1) {
    f->o = 0;
    f->n = 0;
  }
  if (f->v == 1) {
    f->o = 0;
  }
}
/**
 * @brief Вывод для определенных флагов их совместная работа. (l, c, h, o)
 *
 * @param f указатель на структуру флагов
 * @param line количество строк, содержащих шаблон
 * @param file_count количество файлов, в которых был произведен поиск
 * @param filename имя файла
 */
void print(flag *f, int line, int file_count, char *filename) {
  if (f->l == 1 && line > 0 && f->c != 1) {
    printf("%s\n", filename);
  }
  if (f->c == 1 && f->l != 1 && f->h != 1) {
    if (file_count > 1) {
      printf("%s:%d\n", filename, line);
    } else {
      printf("%d\n", line);
    }
  } else if (f->c == 1 && f->l != 1 && f->h == 1) {
    printf("%d\n", line);
  }
  if (f->c == 1 && f->l == 1) {
    if (file_count < 2) {
      if (f->n != 1 && f->o != 1) {
        printf("%d\n%s\n", file_count, filename);
      } else {
        printf("%s:%d\n", filename, line);
      }
    } else {
      if (line && f->h != 1) {
        printf("%s:%d\n", filename, file_count - 1);
        printf("%s\n", filename);
      } else if (!line && f->h != 1) {
        printf("%s:0\n", filename);
      } else if (line && f->h == 1) {
        printf("%d\n%s\n", file_count - 1, filename);
      } else if (!line && f->h == 1) {
        printf("0\n");
      }
    }
  }
}
/**
 * @brief Добавление нового шаблона к существующему
 *
 * @param pattern указатель на массив символов с шаблоном поиска
 * @param str указатель на массив символов с шаблоном поиска который нужно
 * добавить
 */
void grep_e(char *pattern, char *str) {
  if (*pattern != '\0') {
    strcat(pattern, "|");
  }
  strcat(pattern, str);
}
/**
 * @brief Добавление шаблона из файла
 *
 * @param pattern указатель на массив символов с шаблоном поиска
 * @param filename имя файла
 */
void grep_f(char *pattern, char *filename) {
  FILE *fp;
  char str_two[size] = {0};
  fp = fopen(filename, "r");
  if (fp != NULL) {
    while (fgets(str_two, size - 1, fp) != NULL) {
      int line = strlen(str_two);
      if (str_two[line - 1] == '\n') {
        str_two[line - 1] = '\0';
      }
      if (str_two[0] == '\0') {
        strcpy(str_two, ".");
      }
      grep_e(pattern, str_two);
    }
  } else {
    fprintf(stderr, "grep: %s: No such file or directory\n", filename);
  }
  fclose(fp);
}
