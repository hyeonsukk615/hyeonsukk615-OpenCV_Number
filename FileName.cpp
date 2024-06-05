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
                cout << "�ܰ��� ��: " << contours.size() << endl;
            }
            else if (y > 200) {
                /*
                Mat binaryImage = canvas(Rect(1, 1, 498, 498)).clone();
                Mat element = getStructuringElement(MORPH_RECT, Size(40, 40));
                Mat final1, final2;
                threshold(binaryImage, final1, 128, 255, THRESH_BINARY_INV);
                int whitePixelCount = countNonZero(binaryImage);
                int blackPixelCount = binaryImage.total() - whitePixelCount;
                cout << "���(255) �ȼ� ��: " << whitePixelCount << endl;
                cout << "������(0) �ȼ� ��: " << blackPixelCount << endl;
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
    // �̹��� �б�
    Mat image = imread("97_00_00.jpg", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // ����ȭ
    Mat binaryImage;
    threshold(image, binaryImage, 128, 255, THRESH_BINARY);
    Mat element = getStructuringElement(MORPH_RECT, Size(40, 40));
    // �ݱ� ����(Closing)
    Mat closedImage;

    morphologyEx(binaryImage, closedImage, MORPH_CLOSE, element);

    // ���� ����(Opening)
    Mat openedImage;
    morphologyEx(binaryImage, openedImage, MORPH_OPEN, element);

    // 500x500 ������� ��������
    Mat resized500x500;
    resize(closedImage, resized500x500, Size(500, 500));

    // ���������� 100x100 ������� ��������
    Mat finalImage;
    resize(resized500x500, finalImage, Size(100, 100));

    // ��� �̹��� ����
    imwrite("output.jpg", openedImage);
    // ��� �̹��� �����ֱ�
    imshow("Final Image", openedImage);
    waitKey(0);

    return 0;
}
*/
/*
1. �ʱ�ȭ �� ������ ���� 500x700 ũ���� ��� ĵ������ �����մϴ�.
"windows"��� �̸��� �����츦 �����մϴ�. ���콺 �ݹ� �Լ��� �����Ͽ� ���콺 �̺�Ʈ�� ó���մϴ�.

2.���� ���� ���� �������� Set(canvas);�� ȣ���Ͽ� ��ư�� ĵ������ ȭ�鿡 ǥ���մϴ�.

3. ���콺 �̺�Ʈ ó�� (onMouse �Լ�)

���콺 ���� ��ư�� ������ ��.
�Է� ����(500x500) ������ ����� ��带 Ȱ��ȭ�մϴ�.
��ư ����(500 �̻�)���� ������ �۾�(����, �ҷ�����, ����, ����, ����)�� �����մϴ�.

���콺 �̵� ��. ���� ��尡 Ȱ��ȭ�� ���, ���� �׸��ϴ�.

���콺 ���� ��ư�� ���� ��. ����� ��带 ��Ȱ��ȭ�մϴ�.

4. �������̽� ���� (Set �Լ�): ĵ������ ǥ���մϴ�.
��ư ������ �����ϰ� �簢���� �ؽ�Ʈ�� �׷� ����� �������̽��� �����մϴ�.
Save, Load, Clear, Run, Exit ��ư�� �����մϴ�.

5. ĵ���� ����� (Clear �Լ�):Clear ��ư�� Ŭ���Ǿ��� ��, ĵ������ �ʱ� ���·� �ǵ����ϴ�.
�ܼ�â�� "windows Clear" �޽����� ����մϴ�.

6.�� ��ư�� ���
���� ���(save) Save ��ư Ŭ�� ��, �ܼ�â���� ���ϸ��� �Է� �޾� ���� �Է�â�� ������ ���Ϸ� �����մϴ�.
������ ������ 3ä�� �÷� �������� ����˴ϴ�.

���� ���(Clear)Clear ��ư Ŭ�� ��, �Է�â�� ������ �����մϴ�.
Rect contains �Լ��� ����Ͽ� Ŭ���� ������ Ȯ���ϰ� ���콺 �̺�Ʈ�� ó���մϴ�.

�ҷ����� ���(load)Load ��ư Ŭ�� ��, �ܼ�â���� ���ϸ��� �Է� �޾� ������ �ҷ��� �Է�â�� ����մϴ�.

������(Exit) Exit ��ư Ŭ�� ��, ���α׷��� �����մϴ�.
    */
