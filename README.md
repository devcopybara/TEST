# STM32F103 TDD example

STM32CubeIDE로 생성한 NUCLEO-F103RB 프로젝트에 하드웨어와 무관한
`AppCounter` 로직, 호스트 단위 테스트, GitHub Actions CI를 추가한 예제입니다.

## 로컬 테스트

ARM 보드나 크로스 컴파일러 없이 PC의 GCC만으로 실행할 수 있습니다.

```sh
make test
```

Windows에서 MSYS2/MinGW Make를 사용한다면 다음 명령도 가능합니다.

```powershell
mingw32-make test
```

테스트는 실패 시 0이 아닌 종료 코드를 반환하므로 GitHub Actions의 검사 결과에
바로 반영됩니다.

## 펌웨어 빌드

`arm-none-eabi-gcc`가 설치된 환경에서 실행합니다.

```sh
make firmware
```

생성되는 ELF, HEX, BIN, MAP 파일은
`00_CORTEX_12_PRINTF_f103/build/firmware/`에 저장됩니다. CI에서는 이 파일들을
14일 동안 다운로드 가능한 workflow artifact로 보관합니다.

## TDD 진행 방식

1. `tests/test_app_counter.c`에 기대 동작을 먼저 테스트로 작성합니다.
2. `make test`를 실행해 새 테스트가 실패하는지 확인합니다(Red).
3. `Core/Src/app_counter.c`를 최소한으로 수정해 통과시킵니다(Green).
4. 테스트가 계속 통과하는 상태에서 구현과 테스트를 정리합니다(Refactor).

`AppCounter`는 HAL 헤더를 포함하지 않아 호스트에서 빠르게 테스트할 수 있고,
`main.c`에서는 동일한 모듈을 실제 UART 인사말 3회 출력에 사용합니다.

## GitHub 저장소 설정

- `.github/workflows/ci.yml`을 포함해 프로젝트 소스를 커밋하고 푸시합니다.
- 저장소 **Settings > Branches**에서 `main` 보호 규칙을 만들고
  `Host unit tests`, `ARM firmware build` 검사를 필수로 지정합니다.
- Actions의 workflow 권한은 읽기 전용으로 유지합니다. 현재 workflow도
  `contents: read`만 요청합니다.
- 향후 HAL 호출부까지 테스트하려면 HAL wrapper와 mock을 추가하고, 커버리지
  리포트가 필요하면 GCC의 `--coverage`와 gcovr를 별도 job에 연결합니다.

`Debug/`, `Release/`, `build/`는 생성 산출물이므로 Git에서 제외됩니다.
