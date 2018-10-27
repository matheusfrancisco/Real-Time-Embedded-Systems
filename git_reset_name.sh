git filter-branch -f --env-filter "
    GIT_AUTHOR_NAME='matheusfrancisco'
    GIT_AUTHOR_EMAIL='mfranciscobatistamachado@gmail.com'
    GIT_COMMITTER_NAME='matheusfrancisco'
    GIT_COMMITTER_EMAIL='mfranciscobatistamachado@gmail.com'
  " HEAD
