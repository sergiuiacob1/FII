package game_utils;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

public class Dictionary implements IDictionary {
    private Set<String> words;

    Dictionary() {
        words = new HashSet<>();
    }

    public Boolean containsWord(String str) {
        for (String word : words) {
            if (str.equals(word))
                return true;
        }
        return false;
    }

    void generateWords() {
        //aspell words
        try {
            String line;
            FileReader fileReader = new FileReader("./dictionary.txt");
            BufferedReader bufferedReader =
                    new BufferedReader(fileReader);
            while ((line = bufferedReader.readLine()) != null) {
                words.add(line);
            }
            // Always close files.
            bufferedReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("Incorrect dictionary path");
            System.exit(1);
        } catch (IOException e) {
            System.out.println("Couldn't read dictionary");
            e.printStackTrace();
        }
    }

    public Set<String> getWords() {
        return words;
    }

    public void setWords(Set<String> words) {
        this.words = words;
    }
}