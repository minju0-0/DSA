

bool checkPreorder(int* arr, int start, int end, int min, int max){
    if(start > end) return true;
    int root = arr[start];
    if(root <= min || root >= max) return false;
    int i = start + 1;
    while(i <= end && arr[i] < root){
        i++;
    }
    return checkPreorder(arr, start + 1, i - 1, min, root) &&
           checkPreorder(arr, i, end , root, max);
}

bool checkInorder(int* arr, int start, int end, int min, int max){
    if(start > end) return true;
    if(arr[start] <= min || arr[start] >= max) return false;
    for(int i = start; i < end; i++){
        if(arr[i+1] <= min || arr[i+1] >= max) return false;
        if(arr[i] >= arr[i+1]) return false;
    }
    return true;
}

bool checkPostorder(int* arr, int start, int end, int min, int max){
    if(start > end) return true;
    int root = arr[end];
    if(root <= min || root >= max) return false;
    int i = start;
    while(i < end && arr[i] < root){
        i++;
    }
    return checkPostorder(arr, start, i - 1, min, root) &&
           checkPostorder(arr, i, end - 1, root, max);
}

bool checkPreorder(int* array, int size, int& index, int minVal, int maxVal){
       if(index >= size) return true;
       int val = array[index];
       if(val < minVal || val > maxVal) return true;
       
       index++;
       bool left = true;
       if(index < size && array[index] < val) left = checkPreorder(array, size, index, minVal, val);
       bool right = true;
       if(index < size && array[index] > val) right = checkPreorder(array, size, index, val, maxVal);
       
       return left && right;
}

bool checkPostorder(int* array, int size, int& index, int minVal, int maxVal) {
    if (index < 0) return true;
    int val = array[index];
    if (val < minVal || val > maxVal) return true; 

    index--;

    bool right = checkPostorder(array, size, index, val, maxVal);
    bool left = checkPostorder(array, size, index, minVal, val);

    return left && right;
}

int main(){
    
    int size;
    cout << "Enter number of elements: ";
    cin >> size;
    
    int array[size];
    
    cout << "Enter preorder: ";
    for(int i = 0; i < size; i++){
        cin >> array[i];
    }
    
    int i = 0;
    bool res = checkPreorder(array, size, i, -1000000,  1000000);
    if(i == size && res){
        cout << "VALID" << endl;
    } else {
        cout << "INVALID" << endl;
    }
    
    return 0;
}


