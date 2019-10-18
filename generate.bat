@echo off

setlocal
pushd "%~dp0"

set build_folder="%~dp0./build/" || goto :FINALLY

if exist %build_folder% rd /q /s %build_folder% || goto :FINALLY
md %build_folder% || goto :FINALLY
cd %build_folder% || goto :FINALLY

if "%1"=="2019" (
  echo "Generating for Visual studio 2019"
  cmake -G "Visual Studio 16 2019" -A x64 ../ || goto :FINALLY
) else (
  echo "Generating for Visual studio 2017"
  cmake -G "Visual Studio 15 2017" win64 ../ || goto :FINALLY
)

echo Success :)

:FINALLY
  popd
  endlocal

  IF /I "%ERRORLEVEL%" NEQ "0" (
      echo Solution generation failed with error #%ERRORLEVEL%.
      exit /b %ERRORLEVEL%
  )