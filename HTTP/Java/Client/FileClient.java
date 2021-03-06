package test;

import java.io.File;
import java.nio.ByteBuffer;

import org.eclipse.jetty.client.HttpClient;
import org.eclipse.jetty.client.api.ContentResponse;
import org.eclipse.jetty.client.api.Request;
import org.eclipse.jetty.client.api.Response;
import org.eclipse.jetty.client.api.Result;
import org.eclipse.jetty.client.util.StringContentProvider;
import org.eclipse.jetty.http.HttpHeader;
import org.eclipse.jetty.http.HttpMethod;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

public class FileClient {

	public static void main(String[] args) throws Exception  {
		String strFileList = getFileList();
		
		HttpClient httpClient = new HttpClient();
		httpClient.start();
		Request request = httpClient.newRequest("http://127.0.0.1:8080/fileList").method(HttpMethod.POST);
		request.header(HttpHeader.CONTENT_TYPE, "application/json");
		request.content(new StringContentProvider(strFileList,"utf-8"));
		ContentResponse contentRes = request.send();
		System.out.println(contentRes.getContentAsString());		
		httpClient.stop();
	}
	
	// { folder : input , files : [ filename1, filename2,...] }
	private static String getFileList() {
	Gson gson = new Gson();
	JsonObject jo = new JsonObject();
        File directory = new File("./Input");
	jo.addProperty("Folder", "Input");
		
        JsonArray jarr = new JsonArray();
        File[] fList = directory.listFiles();
        for (File file : fList) {
        	jarr.add(file.getName());
        }		
        jo.add("FILES", jarr); // array 는 add로 처리
        
	// json 파일을 전송하기 위해 String으로 만들어 반환
        String res = jo.toString();
        return res; 
	}
}
