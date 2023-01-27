package cz.cvut.fit.tjv.swordrentalserver.business;

import org.springframework.data.repository.CrudRepository;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

//@Transactional(readOnly = true)
public abstract class AbstractCrudService<K, E, R extends CrudRepository<E, K>> {
    protected final R repository;

    protected AbstractCrudService(R repository) {
        this.repository = repository;
    }

//    @Transactional
    public E create(E entity)  {

        return repository.save(entity);
    }

    public Optional<E> readById(K id) {
        return repository.findById(id);
    }

    public List<E> readAll() {
        return (List<E>) repository.findAll();
    }

    public void deleteById(K id) {
        repository.deleteById(id);
    }
}