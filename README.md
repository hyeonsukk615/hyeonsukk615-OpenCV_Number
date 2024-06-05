void save() {

    static int count1 = 0;
    
    count1++;
    
    string Name = to_string(count1) + ".jpg";
    
    Mat save = canvas(Rect(1, 1, 498, 498)).clone();
    
    resize(save, save, Size(500, 500));
    
    imwrite(Name, save);
    
    cout << Name << " file saved" << endl;
    
}

여기부분은 입력시에 파일을 저장할때 파일명을 1씩증가하면서 저장하는 방식으로 0~9 까지의 수의 표본을 만들기위한 코드로 작성하였습니다
to_string(count1) 부분으로 숫자부분을 문자열로 변경하여 저장해서 save 버튼만 눌러도 파일명을 따로 입력할 필요없이 횟수에 따라 자동저장 되는 방식입니다.
