REM @echo off
DEL /F version.h

REM Commit Hash
FOR /F "tokens=*" %%g IN ('git log -1 --pretty^=format:^%%h') do (SET COMMIT_HASH=%%g)

REM Commit Subject
FOR /F "tokens=*" %%g IN ('git log -1 --pretty^=format:^%%s') do (SET COMMIT_SUBJECT=%%g)

REM Commit Date
FOR /F "tokens=*" %%g IN ('git log -1 --pretty^=format:^%%ad') do (SET COMMIT_DATE=%%g)

REM Commit Author and Email
FOR /F "tokens=*" %%g IN ('git log -1 --pretty^=format:^"^%%cn^"') do (SET COMMIT_AUTHOR=%%g)

REM Current Branch
FOR /F "tokens=*" %%g IN ('git rev-parse --abbrev-ref HEAD') do (SET CURRENT_BRANCH=%%g)

REM Changed Files
FOR /F "tokens=*" %%g IN ('git diff-index --name-only HEAD') do (SET OLDEST_CHANGED_FILE_BEFORE_COMMIT=%%g)



echo #pragma once >> version.h

echo #define COMMIT_HASH "%COMMIT_HASH%" >> version.h
echo #define COMMIT_DATE "%COMMIT_DATE%" >> version.h
echo #define COMMIT_SUBJECT "%COMMIT_SUBJECT%" >> version.h
echo #define COMMIT_AUTHOR "%COMMIT_AUTHOR%" >> version.h
echo #define CURRENT_BRANCH "%CURRENT_BRANCH%" >> version.h
echo #define OLDEST_CHANGED_FILE_BEFORE_COMMIT "%OLDEST_CHANGED_FILE_BEFORE_COMMIT%" >> version.h
