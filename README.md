# Unreal 5 C++ FPS Custom

## 소개

언리얼5 C++ 학습을 위한 FPS Sample Project(C++)의 Custom 버전입니다.

Version: 5.4.4

## 추가 내용
- [x] 무기 떨어뜨리기(+물리 적용)
- [Branch: Weapon-Drop](https://github.com/rehomik/Unreal5CustomCppFps/tree/weapon-drop): 무기 해제되나 무기가 공중에 떠있음
- [Branch: Weapon-Drop-with-physics](https://github.com/rehomik/Unreal5CustomCppFps/tree/weapon-drop-with-physics): 해제된 무기는 땅으로 떨어짐.

## Get Started

### 1. Clone

적당한 branch를 clone 합니다.

```
git clone --branch weapon-drop-with-physics https://github.com/rehomik/Unreal5CustomCppFps.git ./
```

🙌 _master 브런치는 정리되어있지 않습니다._<br>
🙌 GitHub Desktop을 이용할 수 있습니다.

### 2. 엔진 실행

EngineDic1Cpp를 통해 엔진을 실행합니다.

Missing EngineDic1Cpp Modules 창은 재컴파일이 필요하다는 메세지 입니다. ok를 눌러 재컴파일 합니다.

### 3. Visual Studio File 생성

Visual Studio File이 없는 상태이므로, 생성합니다.

    엔진 - 툴 - Visual Studio 프로젝트 새로 고침

Visual Studio 열기를 선택하여 정상적으로 열리는지 확인합니다.

### 4. 준비 완료!

정상적으로 실행되는지 확인하세요.

이제 언리얼을 C++과 함께 사용할 수 있습니다.

## 사용 입력

F = 무기 드랍.