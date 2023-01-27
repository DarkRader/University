package cz.cvut.fit.tjv.swordrentalserver.data.entity;

import javax.persistence.*;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

@Entity
@Table(name = "sword")
public class Sword implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private long swordId;
    private String type;
    private long price;
    private long weight;
    private long length;

    @ManyToMany
    private Set<Person> peopleWhoWishesForThisSword = new HashSet<>();

    public Sword(long swordId, String type, long price, long weight, long length, Set<Person> peopleWhoWishesForThisSword) {
        this.swordId = swordId;
        this.type = type;
        this.price = price;
        this.weight = weight;
        this.length = length;
        this.peopleWhoWishesForThisSword = peopleWhoWishesForThisSword;
    }

    public Sword() {}

    public long getSwordId() {
        return swordId;
    }

    public void setSwordId(long swordId) {
        this.swordId = swordId;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public long getPrice() {
        return price;
    }

    public void setPrice(long price) {
        this.price = price;
    }

    public long getWeight() {
        return weight;
    }

    public void setWeight(long weight) {
        this.weight = weight;
    }

    public long getLength() {
        return length;
    }

    public void setLength(long length) {
        this.length = length;
    }

    public Set<Person> getPeopleWhoWishesForThisSword() {
        return peopleWhoWishesForThisSword;
    }

    public void setPeopleWhoWishesForThisSword(Set<Person> peopleWhoWishesForThisSword) {
        this.peopleWhoWishesForThisSword = peopleWhoWishesForThisSword;
    }

    //For tests

//    @Override
//    public boolean equals(Object o) {
//        if (this == o) return true;
//        if (o == null || getClass() != o.getClass()) return false;
//        Sword sword = (Sword) o;
//        return swordId == sword.swordId && price == sword.price && weight == sword.weight && length == sword.length && Objects.equals(type, sword.type) && Objects.equals(peopleWhoWishesForThisSword, sword.peopleWhoWishesForThisSword);
//    }
//
//    @Override
//    public int hashCode() {
//        return Objects.hash(swordId, type, price, weight, length, peopleWhoWishesForThisSword);
//    }
//
//    @Override
//    public String toString() {
//        return "Sword{" +
//                "swordId=" + swordId +
//                ", type='" + type + '\'' +
//                ", price=" + price +
//                ", weight=" + weight +
//                ", length=" + length +
//                ", peopleWhoWishesForThisSword=" + peopleWhoWishesForThisSword +
//                '}';
//    }
}
