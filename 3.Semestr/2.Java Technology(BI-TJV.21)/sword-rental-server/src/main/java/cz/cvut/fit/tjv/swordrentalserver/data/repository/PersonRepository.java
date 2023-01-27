package cz.cvut.fit.tjv.swordrentalserver.data.repository;

import cz.cvut.fit.tjv.swordrentalserver.data.entity.Contract;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Person;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import java.util.Collection;
import java.util.List;
import java.util.Optional;

@Repository
public interface PersonRepository extends CrudRepository<Person, Long> {

}