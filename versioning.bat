@echo off

if "%1"=="" (
    echo Usage: %0 ^<branch_name^>
    exit /b 1
)

set branch=%1

for /f "delims=" %%a in ('powershell -command "(Get-Date).ToUniversalTime().ToString('yyyy-MM-dd')"') do set date_string=%%a
for /f "delims=" %%b in ('powershell -command "(Get-Date).ToUniversalTime().ToString('HH:mm')"') do set time_string=%%b

echo // version.h > include\version.hpp
echo // >> include\version.hpp
echo // Contains version info passed in immediately before compile time. >> include\version.hpp
echo #ifndef VERSION_H >> include\version.hpp
echo #define VERSION_H >> include\version.hpp
echo #include ^<string^> >> include\version.hpp
echo std::string COMPILE_DATE="%date_string%"; >> include\version.hpp
echo std::string COMPILE_TIME="%time_string%"; >> include\version.hpp
echo std::string COMPILE_BRANCH="%branch%"; >> include\version.hpp
echo #endif //VERSION_H >> include\version.hpp