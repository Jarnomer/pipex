<h1 align="center">
  <b>pipex</b>
</h1>

<p align="center">
  <b><i>Bash file redirections and chained unix commands.</i></b><br>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Score-125%2F100-lightgreen?style=for-the-badge" alt="score">
  <img src="https://img.shields.io/github/languages/top/Jarnomer/pipex?style=for-the-badge&logo=c&label=%20&labelColor=gray&color=lightblue" alt="GitHub top language">
	<img src="https://img.shields.io/github/languages/code-size/Jarnomer/pipex?style=for-the-badge&color=lightyellow" alt="GitHub code size in bytes">
  <img src="https://img.shields.io/github/directory-file-count/Jarnomer/pipex/sources?style=for-the-badge&color=pink" alt="GitHub repo file or directory count (in path)">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Type-Solo-violet?style=for-the-badge" alt="type">
  <img src="https://img.shields.io/github/last-commit/Jarnomer/pipex/main?style=for-the-badge&color=red" alt="GitHub last commit (branch)">
</p>

## General

Goal of the project is to run multiple `unix` commands with `execve` by creating child processes with `fork` and communicating between them using `pipe`.

For studies perspective I `highly` recommend that you finish the `bonus` part of this project. It will serve you well in `minishell`.

## Usage

Execution needs an `infile` to open, `two` unix `commands` and `outfile` to `truncate` the result:

```bash
./pipex "Makefile" cat 'wc -l' outfile
```

Will be the same as bash syntax:

```bash
< Makefile cat | wc -l > outfile
```

## Bonus

Bonus supports `heredoc` and `multiple` unix commands. When heredoc is used, result is `appended` to outfile.

```bash
./pipex here_doc EOF cat cat 'wc -l' outfile
```

Will be the same as bash syntax:

```bash
<< EOF cat | cat | wc -l >> outfile
```

Project `passes` many of the 42 `testers`, including [franzinette](https://github.com/xicodomingues/francinette) `strict` excluding quotes and backslashes.

For other information, please refer the main page.

### Cheers and good luck! 🥳