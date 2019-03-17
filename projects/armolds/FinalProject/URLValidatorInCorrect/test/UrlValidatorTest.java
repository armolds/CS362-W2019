import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.Random;
import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {
			
   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   private static int assertFail = 0;
   private static int assertCheck = 0;
   private static int assertFalse = 0;
   private static int assertTrue = 0;
   
   static public void assertFalse(String message, boolean validate){
   if(validate == false) {
      assertFalse++;
   }
   }
   
   static public void assertTrue(String message, boolean validate){
   if(validate == true) {
      assertTrue++;
   }
   }
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   System.out.println("Manual tests:");
	   assertCheck = 0;
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   String[] trueURL = {
	      "https://www.gmail.com",
	      "http://www.gmail.com/!",
	      "ftp://www.gmail.com/#$?$#",
	      "http://www.12345.com",
	      "http://www.stackoverflow.com",
	      "http://gmail.com/$location",
	      "http://www.gmail.com:10",
	      "http://www.gmail.com:10000",
	      "http://localhost/"
	   };

	   String[] falseURL = {
	      "://gmail.com",
	      "http://skdew.outt",
	      "http://www.gmail.com:-50",
	      "http://gmail.com/new//",
	      "http://gm<><>ail.com/here",
	      "http:/gmail.com",
	      "12htp://www.gmail.com",
	      "http://257.257.257.257:90/testing",
	      "http://gmail.com/..."
	   };

	   boolean result = false;
			   
	   for(int i = 0; i < trueURL.length; i++) {
		   try {
			   result = urlVal.isValid(trueURL[i]);
		   } catch (Throwable t)
		   {
		        	  System.out.println("Error caught for URL " + trueURL[i] + " :" + t);
		   }
		   
		   
	      assertTrue( ("This URL is true: " + trueURL[i]), result);
	   }

	   result = false;
	   
	   for(int i = 0; i < falseURL.length; i++) {
		   try {
			   result = urlVal.isValid(falseURL[i]);
		   } catch (Throwable t)
		   {
	        	  System.out.println("Error caught for URL " + falseURL[i] + " :" + t);

		   }
	      assertFalse( ("This URL is true: " + falseURL[i]), result);
	   }

	   System.out.println("REPORT:");
	   System.out.println("Expected Failed: " + falseURL.length);
	   System.out.println("Actual Failed: " + assertFalse);
	   System.out.println("Expected Failed: " + trueURL.length);
	   System.out.println("Actual Failed: " + assertTrue);

   }
   

/*****************************************************************************
 * 
 * Random Testing
 *****************************************************************************/
/*
  ~~A URL IS MADE UP OF 5 PARTS
  ~~These test will partition and then randomly test each part:
	   1)scheme
	   2)authority
	   3)port
	   4)path
	   5)query	   
*/  
   
   protected String createRandomString(int length) {
       String letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890+.-!_}{;<>";
       StringBuilder s = new StringBuilder();
       Random rnd = new Random();
       while (s.length() < length) { // length of the random string.
           int index = (int) (rnd.nextFloat() * letters.length());
           s.append(letters.charAt(index));
       }
       String str = s.toString();
       return str;

   }
   
   protected String createRandomNumericString(int length) {
       String letters = "1234567890";
       StringBuilder s = new StringBuilder();
       Random rnd = new Random();
       while (s.length() < length) { // length of the random string.
           int index = (int) (rnd.nextFloat() * letters.length());
           s.append(letters.charAt(index));
       }
       String str = s.toString();
       return str;

   }
   
   protected String createRandomURL(int length) {
       String letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890+.-////:";
       StringBuilder s = new StringBuilder();
       Random rnd = new Random();
       while (s.length() < length) { // length of the random string.
           int index = (int) (rnd.nextFloat() * letters.length());
           s.append(letters.charAt(index));
       }
       String str = s.toString();
       return str;

   }
   
   protected int numberOfTests(int testNumber) {
	   switch(testNumber) {
	   		case 1: 
	   			//scheme
	   			return 100;
	   		case 2:
	   			//authority
	   			return 100;
	   		case 3:
	   			//port
	   			return 100;
	   		case 4:
	   			//path
	   			return 100;
	   		case 5:
	   			//query
	   			return 100;
	   		default:
	   			return 0;  
	   }
		   
   }
   
   
   public void testPartition_Scheme()
   {
	   Random rand = new Random();
	   int n = numberOfTests(1);
	   int i;
	   String suffix = "://www.apache.org";
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	   
	   System.out.print("\n\n*****  TESTING: Scheme  *****\n");
	   for (i = 0; i < n; i++ ) {
		   int size = rand.nextInt(5)+1;
		   String url = createRandomString(size) + suffix;
		   
		   try {
			   assertTrue(urlVal.isValid(url));  
			   System.out.print("VALID SCHEME: " + url + "\n");
			   
		   } catch(Throwable t) {
			   //assertTrue(false);
			   System.out.print("ERROR! BUG CAUSED BY SCHEME: " + url + "\n");
		   }
	   }
   }
   
   
   
   public void testPartition_Authority(){
	   Random rand = new Random();
	   int n = numberOfTests(2);
	   int i;
	   String prefix = "http://";
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	   
	   System.out.print("\n\n*****  TESTING: Authority  *****\n");
	   for (i = 0; i < n; i++ ) {
		   int size = rand.nextInt(50)+1;
		   String url = prefix + createRandomString(size) ;
		   
		   try {
			   assertTrue(urlVal.isValid(url));  
			   System.out.print("VALID AUTHORITY: " + url + "\n");
		   } catch(Throwable t) {
			   System.out.print("ERROR! BUG CAUSED BY AUTHORITY: " + url + "\n");
		   }
	   }
   }
   
   
   public void testPartition_Port(){
	   Random rand = new Random();
	   int n = numberOfTests(3);
	   int i;
	   String prefix = "http://www.apache.org:";
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	   
	   System.out.print("\n\n*****  TESTING: Ports  *****\n");
	   for (i = 0; i < n; i++ ) {
		   int size = rand.nextInt(5)+1;
		   String url = prefix + createRandomNumericString(size) ;
		   
		   try {
			   assertTrue(urlVal.isValid(url));  
			   System.out.print("VALID PORT: " + url + "\n");
		   } catch(Throwable t) {
			   System.out.print("ERROR! BUG CAUSED BY PORT: " + url + "\n");
		   }
	   }
   }
   
   public void testPartition_Path(){
	   Random rand = new Random();
	   int n = numberOfTests(4);
	   int i;
	   String prefix = "http://www.apache.org/";
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	   
	   System.out.print("\n\n*****  TESTING: Paths  *****\n");
	   for (i = 0; i < n; i++ ) {
		   int size = rand.nextInt(50)+1;
		   String url = prefix + createRandomString(size) ;
		   
		   try {
			   assertTrue(urlVal.isValid(url));  
			   System.out.print("VALID PATH: " + url + "\n");
		   } catch(Throwable t) {
			   System.out.print("ERROR! BUG CAUSED BY PATH: " + url + "\n");
			  	
		   }
	   }   

   }
 
   
   public void testPartition_Query(){
	   Random rand = new Random();
	   int n = numberOfTests(5);
	   int i;
	   String prefix = "http://www.apache.org?";
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	   
	   System.out.print("\n\n*****  TESTING: Queries  *****\n");
	   for (i = 0; i < n; i++ ) {
		   int size = rand.nextInt(25);
		   String url = prefix + createRandomString(size) ;
		   
		   try {
			   assertTrue(urlVal.isValid(url));  
			   System.out.print("VALID QUERY: " + url + "\n");
		   } catch(Throwable t) {
			   System.out.print("ERROR! BUG CAUSED BY QUERY: " + url + "\n");
		   }
	   }  	   

   }
 
   
   /****************************END RANDOM TESTING********************/
   
   public boolean assertIsTrue(boolean value1, boolean value2)
   {
	   if (value1 == value2){
		   return true;
	   }
	   else {
		   return false;
	   }
   }
   
   
   public void testIsValidFILEINPUT() 
   {
	   //You can use this function for programming based testing
	   int totalFailures = 0;

	      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES + 
	    		  UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_LOCAL_URLS + UrlValidator.NO_FRAGMENTS);
	      int failures = 0;
	      int urlsTested = 0;
			try {
				System.out.println("***START FILE INPUT TEST***");
				File file = new File("test.txt");
				FileReader fileReader = new FileReader(file);
				BufferedReader bufferedReader = new BufferedReader(fileReader);
				String line;
				while ((line = bufferedReader.readLine()) != null) {
					
					String testLine = new String();
			        String url = new String();
			        String expResult = new String(); 
			        
					testLine = line;

			        url = testLine.substring(0, testLine.indexOf(","));
			        expResult = testLine.substring(testLine.indexOf(",")+2, testLine.length());
			        
			        boolean expected; 
			        
			        if(expResult.equals("true")) {
			        	expected = true;
			        }
			        else {
			        	expected = false;
			        }
			        
				      boolean result = false;
				      
			          try  {
			          result = urlVal.isValid(url);
			          } catch (Throwable t)
			          {
			        	  System.out.println("Error caught for URL " + url + " :" + t);
			          }
				      
				      if(!assertIsTrue(result, expected)) {
				    	  System.out.println("Test Failed: " + url + " Expected Result: " + expected +
				    	  " Actual Result: " + result);
				    	  failures++;
				    	  totalFailures++;
				      }
				      
				    	 urlsTested++; 
				      }
				fileReader.close();

			} catch (IOException e) {
				e.printStackTrace();
			}

	      System.out.println("Number of Tests Failed: " + failures + " out of " + urlsTested + " URLs tested");
	      System.out.println("");
	      assertEquals(totalFailures, 0);

   } 
   
   
   public void testIsValidALLOWALLSCHEMES() {
	   //second programming based test - ALLOW ALL SCHEMES
	   int totalFailures = 0;
	   int failures = 0;
	   int urlsTested = 0;
	      
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("***START ALLOW ALL SCHEMES TEST***");
	   for (int i = 0; i < validURLs.length; i++) {
		   boolean result = false;
		   String url = validURLs[i];
		  
	          try  {
	          result = urlVal.isValid(url);
	          } catch (Throwable t)
	          {
	        	  System.out.println("Error caught for URL " + url + " :" + t);
	          }
		   
		   if(!result) {
		    	  System.out.println("Test Failed: " + url + " Expected Result: true " + 
		    	  " Actual Result: " + result);
		    	  failures++;
		    	  totalFailures++;
		   }
		   urlsTested++;
	   }
	   
	   for (int i = 0; i < invalidURLs.length; i++) {
		   boolean result = false;
		   String url = invalidURLs[i];
		  
	          try  {
	          result = urlVal.isValid(url);
	          } catch (Throwable t)
	          {
	        	  System.out.println("Error caught for URL " + url + " :" + t);
	          }
		   
		   if(result) {
		    	  System.out.println("Test Failed: " + url + " Expected Result: false " + 
		    	  " Actual Result: " + result);
		    	  failures++;
		    	  totalFailures++;
		   }
		   urlsTested++;
	   }
	      
	   	  System.out.println("Number of Tests Failed: " + failures + " out of " + urlsTested + " URLs tested");
	      System.out.println("");
	      assertEquals(totalFailures, 0);
	   
   }
   
   public void testIsValidFTPSchemes() {
	   //third programming based test - ftp schemes only
	   int totalFailures = 0;
	   int failures = 0;
	   int urlsTested = 0;
	   String[] schemes = {"ftp"}; 

	   UrlValidator urlVal = new UrlValidator(schemes);
	   System.out.println("***START FTP SCHEME TEST***");
	   for(int i = 0; i < validURLs.length; i++)
	   {
		   boolean result = false;
		   boolean expected = false;
		   String url = validURLs[i];
		   if(url.startsWith("ftp")) {
			   expected = true;
		   }
		   
	          try  {
	          result = urlVal.isValid(url);
	          } catch (Throwable t)
	          {
	        	  System.out.println("Error caught for URL " + url + " :" + t);
	          }
	          
	          if(result != expected) {
		    	  System.out.println("Test Failed: " + url + " Expected Result: " + expected +
		    	  " Actual Result: " + result);  
		    	  failures++;
		    	  totalFailures++;
	          }
		   urlsTested++;
	   }
	   
	   	  System.out.println("Number of Tests Failed: " + failures + " out of " + urlsTested + " URLs tested");
	      System.out.println("");
	      assertEquals(totalFailures, 0);
	   
   }
   
   // ALLOW_2_SLASHES - [FALSE] Allows double '/' characters in the path component.
   // NO_FRAGMENT- [FALSE] By default fragments are allowed, if this option is included then fragments are flagged as illegal.
   // ALLOW_ALL_SCHEMES - [FALSE] By default only http, https, and ftp are considered valid schemes. Enabling this option will let any scheme pass validation.

   
   //Valid URL Set
   String[] validURLs = {"http://www.yahoo.com",
		   				 "ftp://go.com",
		   				 "https://www.apache.org:80/path",
		   				 "h3t://go.au",
		   				 "http://255.255.255.255",
		   				 "https://12345.com/testPath",
		   				 "ftp://abc.com:80"
   };
   
   
   //Invalid URL Set
   String[] invalidURLs = {"2340ieijdfaklldjfsLAEJRO23WEIURJWIOEFNAKJD",
		   				   "://www.google.com",
		   				   "tpf://go.com",
		   				   "http://go.1aa./path",
		   				   "http://go.1aa",
		   				   "http:0.0.0.0",
		   				   "http://google.com:80/test test"		   
   };
   
   }
   

