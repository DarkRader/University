package cz.cvut.fit.tjv.swordrentalserver.data.repository;

import cz.cvut.fit.tjv.swordrentalserver.data.entity.Contract;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Person;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Sword;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import java.util.Collection;

@Repository
public interface ContractRepository extends CrudRepository<Contract, Long> {
    Collection<Contract> findAllByPerson(Person person);

    Collection<Sword> findAllBySword(Sword sword);
}
