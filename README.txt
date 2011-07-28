OpenCV를 이용한 회로도 인식 툴.
회로도 사진을 입력받아 회로의 파트들과
연결 상태를 인식한 후 spice에 돌릴 수 있는
.cir 파일을 출력한다.

Recognition.cpp 파일의 FindElement함수와 Wiring함수에
인식 코드를 추가하면 인식 결과를 Recognized Circuit Image창으로
확인 할 수 있다.

빌드하기 위하여...
프로젝트를 빌드하기 위해서는 opencv라이브러리를
프로젝트에 링크하여야 한다.
