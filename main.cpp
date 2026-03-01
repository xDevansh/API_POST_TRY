#include<iostream>
#include<string>
#include<curl/curl.h>

//1.helper function
//a callback function which curl calls after getting the respone
size_t WriteCallback(void* contents, size_t size, size_t nmemb,std::string* user_string)
{
    user_string->append((char*)contents,size*nmemb);
    return size*nmemb;
}

int main(){
    CURL* curl;
    CURLcode res;
    std::string server_reply;

    //2. data we are sending as json string
    std::string my_post_data="{\"title\": \"My C++ Post\", \"body\": \"Hello from Bharata!\", \"userId\": 1}";

    //start the handle
    curl = curl_easy_init();

    if(curl)
    {
        //3. setting the endpoint
        curl_easy_setopt(curl,CURLOPT_URL,"https://jsonplaceholder.typicode.com/posts");

        //4. setting up the callback to catch the response
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteCallback);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&server_reply);

        //5. attach data(convert our cpp string to c style string)
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,my_post_data.c_str());

        //6. creating our header list
        struct curl_slist* headers=NULL;
        headers=curl_slist_append(headers,"Content-Type: application/json");

        //send the header list to curl
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);

        res=curl_easy_perform(curl);

        //cleaning up header list and the handle
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        //printing sserver's reply
        std::cout<<"____ SSERVER REPLY ____\n";
        std::cout<<server_reply<<std::endl;

    }

    return 0;
}