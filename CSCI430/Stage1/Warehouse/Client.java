import java.util.*;
import java.io.*;
public class Member implements Serializable {
  private static final long serialVersionUID = 1L;
  private String name;
  private String address;
  private String phone;
  private String id;
  private static final String MEMBER_STRING = "M";
  private List<Book> booksBorrowed = new LinkedList();
  private List booksOnHold = new LinkedList();
  private List transactions = new LinkedList();
  public  Member (String name, String address, String phone) {
    this.name = name;
    this.address = address;
    this.phone = phone;
    id = MEMBER_STRING + (MemberIdServer.instance()).getId();
  }

  public String getName() {
    return name;
  }
  public String getPhone() {
    return phone;
  }
  public String getAddress() {
    return address;
  }
  public String getId() {
    return id;
  }
  public void setName(String newName) {
    name = newName;
  }
  public void setAddress(String newAddress) {
    address = newAddress;
  }
  public void setPhone(String newPhone) {
    phone = newPhone;
  }
  public boolean equals(String id) {
    return this.id.equals(id);
  }
  public String toString() {
    String string = "Member name " + name + " address " + address + " id " + id + "phone " + phone;
    return string;
  }
  //--------------------//
  
  public boolean issue(Book book) {
	  
	  booksBorrowed.add(book);
	  System.out.println(this.getName() + " reserved "+ book.getTitle());
	  return true;
  }
  
  public void printBooksBorrowed() {
	  System.out.println("Books checked out to "+this.getName());
	  System.out.println(" ID,Title ");
	  for (Book i: booksBorrowed) {
		  System.out.println(i.getId()+", "+i.getTitle());
	  }
  }
  
}