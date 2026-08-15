@echo off
cd /d "%~dp0"
echo Starting local handbook at http://localhost:8000
python -m http.server 8000
