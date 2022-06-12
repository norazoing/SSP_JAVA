using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;

namespace SP_TEST
{
    class Program
    {
        static void Main(string[] args)
        {
            HttpListener listener = new HttpListener();
            listener.Prefixes.Add("http://127.0.0.1:8080/");
            listener.Start();

            while(true)
            {
                var context = listener.GetContext();
                Console.WriteLine("Request : " + context.Request.Url);
                byte[] data = Encoding.UTF8.GetBytes("HelloWorld");
                context.Response.OutputStream.Write(data, 0, data.Length);
                context.Response.StatusCode = 200;
                context.Response.Close();
            }
        }
    }
}
