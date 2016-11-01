import java.util.*;
import java.lang.*;
import java.io.*;
public class Book implements Serializable {
  private static final long serialVersionUID = 1L;
  private String title;
  private String author;
  private String id;
  private boolean checkedOut;
  private Member owner;


  public Book(String title, String author, String id) {
    this.title = title;
    this.author = author;
    this.id = id;
    checkedOut = false;
    owner = null;
  }

  public String getAuthor() {
    return author;
  }
  public String getTitle() {
    return title;
  }
  public String getId() {
    return id;
  }
  public boolean getCheckedOut() {
    return checkedOut;
  }
  public void checkoutBook(Member newOwner){
    this.checkedOut = true;
    this.owner = newOwner;
  }
  public void returnBook() {
    this.checkedOut = false;
    this.owner = null;
  }

  public String toString() {
       
      return (owner == null)?  "title " + title + " author " + author + " id " + id +""
                     :  "title " + title + " author " + author + " id " + id + " Checked out to "+ owner.getName();
  }
  
 //--------------------------//
  public boolean issue(Member member) {
	  return true;
  }
  
}
