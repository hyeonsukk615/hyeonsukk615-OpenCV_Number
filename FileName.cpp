#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void* userdata);
void Set(Mat canvas);
void Clear(int x, int y, Mat canvas);
Mat canvas(500, 900, CV_8UC3, Scalar(255, 255, 255));// windows img
void save();
void load();

int main() {
    namedWindow("windows", WINDOW_AUTOSIZE);// window named set
    setMouseCallback("windows", onMouse, &canvas);// mouse call back
    while (true) {
        Set(canvas);
        char key = waitKey(10);
    }
    return 0;
}

void onMouse(int event, int x, int y, int flags, void* userdata) {// Mouse event function
    static bool drawing = false;
    static Point prevPoint(-1, -1);
    Mat canvas = *(Mat*)userdata;
    Rect area(0, 0, 500, 500);// img area
    int count = 0;
    switch (event) {
    case EVENT_LBUTTONDOWN:// mouse L down
        prevPoint = Point(x, y);
        if (area.contains(Point(x, y))) { drawing = true; }// 500,500 area inspect
        if (500 < x && x < 600) {// draw area
            if (y > 400) { exit(1); }// exit area
            else if (y > 300) { // run area
                cout << "run" << endl;
            }
            else if (y > 200) { Clear(x, y, canvas); }// clear area
            else if (y > 100) { load(); }// load area
            else if (y > 0) { save(); }// save area
        }
        else if (700 < x && x < 900) {
            if (y > 400) { cout << "counter5" << endl; }// exit area
            else if (y > 300) {
                Mat binaryImage = canvas(Rect(1, 1, 498, 498)).clone();
                Mat element = getStructuringElement(MORPH_RECT, Size(40, 40));
                Mat final1, final2;
                cvtColor(binaryImage, final1, COLOR_BGR2GRAY);
                threshold(final1, final2, 128, 255, THRESH_BINARY_INV);
                morphologyEx(final2, final2, MORPH_OPEN, element);
                vector<vector<Point>> contours;
                findContours(final2, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
                cout << "외곽선 수: " << contours.size() << endl;
            }
            else if (y > 200) {
                /*
                Mat binaryImage = canvas(Rect(1, 1, 498, 498)).clone();
                Mat element = getStructuringElement(MORPH_RECT, Size(40, 40));
                Mat final1, final2;
                threshold(binaryImage, final1, 128, 255, THRESH_BINARY_INV);
                int whitePixelCount = countNonZero(binaryImage);
                int blackPixelCount = binaryImage.total() - whitePixelCount;
                cout << "흰색(255) 픽셀 수: " << whitePixelCount << endl;
                cout << "검은색(0) 픽셀 수: " << blackPixelCount << endl;
                */
            }// clear area
            else if (y > 100) {
                Mat binaryImage = canvas(Rect(1, 1, 498, 498)).clone();
                Mat element = getStructuringElement(MORPH_RECT, Size(40, 40));
                Mat final1;
                threshold(binaryImage, final1, 128, 255, THRESH_BINARY_INV);
                imshow("Final Image", final1);
            }// load area
            else if (y > 0) {
                Mat binaryImage = canvas(Rect(1, 1, 498, 498)).clone();
                Mat element = getStructuringElement(MORPH_RECT, Size(40, 40));
                Mat final1;
                morphologyEx(binaryImage, final1, MORPH_OPEN, element);
                morphologyEx(final1, final1, MORPH_OPEN, element);
                imshow("Final Image", final1);

            }// save area
        }
    case EVENT_MOUSEMOVE:// mouse move
        if (drawing) {
            if (500 > x) {
                line(canvas, prevPoint, Point(x, y), Scalar(0, 0, 0), 10);
                prevPoint = Point(x, y);
            }
        }
        break;
    case EVENT_LBUTTONUP:// mouse L up
        drawing = false;
        break;
    }
}

void Set(Mat canvas) { // interface function
    imshow("windows", canvas); // img print
    Rect saveButton(500, 0, 200, 100);// button
    Rect loadButton(500, 100, 200, 100);
    Rect clearButton(500, 200, 200, 100);
    Rect runButton(500, 300, 200, 100);
    Rect exitButton(500, 400, 200, 100);
    Rect counter1Button(700, 0, 200, 100);
    Rect counter2Button(700, 100, 200, 100);
    Rect counter3Button(700, 200, 200, 100);
    Rect counter4Button(700, 300, 200, 100);
    Rect counter5Button(700, 400, 200, 100);
    rectangle(canvas, saveButton, Scalar(0, 0, 0), 2);// text
    putText(canvas, "Save", Point(saveButton.x + 10, saveButton.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 3);
    rectangle(canvas, loadButton, Scalar(0, 0, 0), 2);
    putText(canvas, "Load", Point(loadButton.x + 10, loadButton.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 3);
    rectangle(canvas, clearButton, Scalar(0, 0, 0), 2);
    putText(canvas, "Clear", Point(clearButton.x + 10, clearButton.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 3);
    rectangle(canvas, runButton, Scalar(0, 0, 0), 2);
    putText(canvas, "Run", Point(runButton.x + 10, runButton.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 3);
    rectangle(canvas, exitButton, Scalar(0, 0, 0), 2);
    putText(canvas, "Exit", Point(exitButton.x + 10, exitButton.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 3);
    rectangle(canvas, counter1Button, Scalar(0, 0, 0), 2);
    putText(canvas, "counter1", Point(counter1Button.x + 10, counter1Button.y + 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 3);
    rectangle(canvas, counter2Button, Scalar(0, 0, 0), 2);
    putText(canvas, "counter2", Point(counter2Button.x + 10, counter2Button.y + 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 3);
    rectangle(canvas, counter3Button, Scalar(0, 0, 0), 2);
    putText(canvas, "counter3", Point(counter3Button.x + 10, counter3Button.y + 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 3);
    rectangle(canvas, counter4Button, Scalar(0, 0, 0), 2);
    putText(canvas, "counter4", Point(counter4Button.x + 10, counter4Button.y + 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 3);
    rectangle(canvas, counter5Button, Scalar(0, 0, 0), 2);
    putText(canvas, "counter5", Point(counter5Button.x + 10, counter5Button.y + 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 3);
}

void Clear(int x, int y, Mat canvas) {// clear function
    Rect clearButton(500, 200, 200, 100);
    if (clearButton.contains(Point(x, y))) {
        canvas = (500, 700, CV_8UC3, Scalar(255, 255, 255));
        cout << "windows Clear" << endl;
        Set(canvas);
    }
}

void save() {
    static int count1 = 40;
    count1++;
    string Name = to_string(count1) + ".jpg";
    Mat save = canvas(Rect(1, 1, 498, 498)).clone();
    resize(save, save, Size(500, 500));
    /*
    cout << "save file name : ";
    cin >> Name;
    */
    imwrite(Name, save);
    cout << Name << " file saved" << endl;
}

void load() {
    string Name = "";
    cout << "load file name: ";
    cin >> Name;
    Mat number = imread(Name);
    number.copyTo(canvas(Rect(0, 0, 500, 500)));
}

/*
#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main() {
    // 이미지 읽기
    Mat image = imread("97_00_00.jpg", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // 이진화
    Mat binaryImage;
    threshold(image, binaryImage, 128, 255, THRESH_BINARY);
    Mat element = getStructuringElement(MORPH_RECT, Size(40, 40));
    // 닫기 연산(Closing)
    Mat closedImage;

    morphologyEx(binaryImage, closedImage, MORPH_CLOSE, element);

    // 열린 연산(Opening)
    Mat openedImage;
    morphologyEx(binaryImage, openedImage, MORPH_OPEN, element);

    // 500x500 사이즈로 리사이즈
    Mat resized500x500;
    resize(closedImage, resized500x500, Size(500, 500));

    // 최종적으로 100x100 사이즈로 리사이즈
    Mat finalImage;
    resize(resized500x500, finalImage, Size(100, 100));

    // 결과 이미지 저장
    imwrite("output.jpg", openedImage);
    // 결과 이미지 보여주기
    imshow("Final Image", openedImage);
    waitKey(0);

    return 0;
}
*/
/*
1. 초기화 및 윈도우 설정 500x700 크기의 흰색 캔버스를 생성합니다.
"windows"라는 이름의 윈도우를 생성합니다. 마우스 콜백 함수를 설정하여 마우스 이벤트를 처리합니다.

2.메인 루프 무한 루프에서 Set(canvas);를 호출하여 버튼과 캔버스를 화면에 표시합니다.

3. 마우스 이벤트 처리 (onMouse 함수)

마우스 왼쪽 버튼을 눌렀을 때.
입력 영역(500x500) 내에서 드로잉 모드를 활성화합니다.
버튼 영역(500 이상)에서 적절한 작업(저장, 불러오기, 삭제, 실행, 종료)을 수행합니다.

마우스 이동 시. 로잉 모드가 활성화된 경우, 선을 그립니다.

마우스 왼쪽 버튼을 뗐을 때. 드로잉 모드를 비활성화합니다.

4. 인터페이스 설정 (Set 함수): 캔버스를 표시합니다.
버튼 영역을 정의하고 사각형과 텍스트를 그려 사용자 인터페이스를 설정합니다.
Save, Load, Clear, Run, Exit 버튼을 설정합니다.

5. 캔버스 지우기 (Clear 함수):Clear 버튼이 클릭되었을 때, 캔버스를 초기 상태로 되돌립니다.
콘솔창에 "windows Clear" 메시지를 출력합니다.

6.각 버튼의 기능
저장 기능(save) Save 버튼 클릭 시, 콘솔창에서 파일명을 입력 받아 현재 입력창의 영상을 파일로 저장합니다.
저장할 영상은 3채널 컬러 영상으로 저장됩니다.

삭제 기능(Clear)Clear 버튼 클릭 시, 입력창의 내용을 삭제합니다.
Rect contains 함수를 사용하여 클릭된 영역을 확인하고 마우스 이벤트로 처리합니다.

불러오기 기능(load)Load 버튼 클릭 시, 콘솔창에서 파일명을 입력 받아 영상을 불러와 입력창에 출력합니다.

종료기능(Exit) Exit 버튼 클릭 시, 프로그램을 종료합니다.
    */
