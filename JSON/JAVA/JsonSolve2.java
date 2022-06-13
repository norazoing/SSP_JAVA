import java.io.FileReader;
import java.io.IOException;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.stream.JsonReader;

public class JsonSolve2 {

	public static void main(String[] args) {
		String filePath = "sample.json";
		try {
			Gson gson = new Gson();
			JsonReader reader = new JsonReader(new FileReader(filePath));
			JsonObject jsonObj = gson.fromJson(reader, JsonObject.class);

			String name = jsonObj.get("name").getAsString(); // 타입을 아는 경우
			int age = jsonObj.get("age").getAsInt(); // 타입을 아는 경우만 사용
			System.out.println("name:"+name + "("+age+")");
			
		        // Json Array선언해서 get(1)은 두번째 배열에 있는 name과 age를 가져와서 출력 c언어 배열인덱스처럼
			JsonArray jsonArr = jsonObj.get("children").getAsJsonArray();
			JsonObject jsonObj2 = jsonArr.get(1).getAsJsonObject();
			name = jsonObj2.get("name").getAsString();
			age = jsonObj2.get("age").getAsInt();
			System.out.println("name:"+name + "("+age+")");
					
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

/*{"name":"spiderman",
 * "age":45,"married":true,
 * "specialty":["martial art","gun"],
 * "vaccine":{"1st":"done","2nd":"expected","3rd":null},
 * "children":[{"name":"spiderboy","age":10},{"name":"spidergirl","age":8}],
 * "address":null}
 */
