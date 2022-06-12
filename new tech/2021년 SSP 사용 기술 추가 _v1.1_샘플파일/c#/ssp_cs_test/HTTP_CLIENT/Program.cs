using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Http;

namespace SP_TEST
{
    class Program
    {
        static void Main(string[] args)
        {
            HttpClient client = new HttpClient();
            var res = client.GetAsync("http://127.0.0.1:8080/helloworld").Result;
            Console.WriteLine("Response : " + res.StatusCode + " - " + res.Content.ReadAsStringAsync().Result);
           
        }
    }
}
