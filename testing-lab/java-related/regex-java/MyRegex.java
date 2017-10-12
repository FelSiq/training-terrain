import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class MyRegex {
	public static void main(String[] args) {
		Pattern p = Pattern.compile("(Number)( *+= *+)([0-9]+)");
		System.out.println(p.matcher("          .Number=987398").matches());

		Matcher myMatcher = p.matcher("          .Number =    9873   Number     = 98 Number = 8372  Number  =732");
		while (myMatcher.find())
			System.out.println(myMatcher.group(1) + '/'
				+ myMatcher.group(2) + '/' 
				+ myMatcher.group(3));
	}
}