/**
 * Yaf Session
 */
/**
 * @namespace
 */
namespace Yaf;

class Session implements \Iterator, \ArrayAccess, \Countable
{
    /**
     * @var Yaf_Session instance
     */
    protected static _instance;
    /**
     * @var array holds the session data
     */
    public session;
    /**
     * @var bool whether the session was already started or not
     */
    public started = false;
    protected function __clone() -> void
    {
    }
    
    protected function __construct() -> void
    {
    }
    
    /**
     * Defined by Countable interface
     *
     * @return int
     */
    public function count() -> int
    {
        
        return count(this->session);
    }
    
    /**
     * Defined by Iterator interface
     *
     * @return mixed
     */
    public function current()
    {
        
        return current(this->session);
    }
    
    public function del(name)
    {
        
        return this->offsetUnset(name);
    }
    
    public function __destruct() -> void
    {
    }
    
    /**
     * Magic function so that $obj->value will work.
     *
     * @param string $name
     * @return mixed
     */
    public function __get(string name)
    {
        var result;
    
        let result =  null;
        
        if name == null {
            
            return null;
        }
        
        if array_key_exists(name, this->session) {
            let result = this->session[name];
        } else {
            
            if array_key_exists(name, _SESSION) {
                let result = _SESSION[name];
            }
        }
        
        return result;
    }
    
    /**
     * Retrieve singleton instance
     *
     * @return Yaf_Session
     */
    public static function getInstance()
    {
        if self::_instance === null {
            let self::_instance =  new self();
            self::start();
        }
        
        return self::_instance;
    }
    
    public function has(name)
    {
        
        return this->offsetExists(name);
    }
    
    /**
     * Support isset() overloading on PHP 5.1
     *
     * @param string $name
     * @return boolean
     */
    public function __isset(string name) -> boolean
    {
        
        return 
        isset this->session[name] ? true : isset _SESSION[name];
    }
    
    /**
     * Defined by Iterator interface
     *
     * @return mixed
     */
    public function key()
    {
        
        return key(this->session);
    }
    
    /**
     * Defined by Iterator interface
     *
     */
    public function next() -> void
    {
        next(this->session);
    }
    
    /**
     * Support isset() overloading on PHP 5.1
     *
     * @param string $name
     * @return boolean
     */
    public function offsetExists(string name) -> boolean
    {
        
        return this->__isset(name);
    }
    
    /**
     * Return a session value specified by name
     * @param  string $name
     * @return mixed
     */
    public function offsetGet(string name)
    {
        
        return this->__get(name);
    }
    
    /**
     * Set a key of the session with value
     * @param  string $name
     * @param  string $value
     * @return void
     */
    public function offsetSet(string name, string value)
    {
        
        return this->__set(name, value);
    }
    
    /**
     * Support unset() overloading on PHP 5.1
     *
     * @param  string $name
     * @return void
     */
    public function offsetUnset(string name)
    {
        unset(this->session[name]);
        
        unset(_SESSION[name]);
    
    }
    
    /**
     * Defined by Iterator interface
     *
     */
    public function rewind() -> void
    {
        reset(this->session);
    }
    
    /**
     * Allow setting of a session variable.
     * Throw an exception if the name is not string.
     *
     * @param  string $name
     * @param  mixed  $value
     * @throws Yaf_Exception
     * @return void
     */
    public function __set(string name, value)
    {
        if is_string(name) {
            let this->session[name] = value;
            let _SESSION[name] = value;
        } else {
            throw new Exception("Expect a string key name");
        }
    }
    
    protected function __sleep() -> void
    {
    }
    
    /**
     * Starts the session
     */
    public static function start()
    {
        var session;
    
        let session =  self::getInstance();
        
        if session->started == true {
            
            return true;
        } else {
            session_start();
            let session->started =  true;
            let session->session = _SESSION;
        }
    }
    
    /**
     * Support unset() overloading on PHP 5.1
     *
     * @param  string $name
     * @return void
     */
    public function __unset(string name)
    {
        unset(this->session[name]);
    
    }
    
    /**
     * Defined by Iterator interface
     *
     * @return boolean
     */
    public function valid() -> boolean
    {
        var key;
    
        let key =  key(this->session);
        
        return 
        key == null || key == false ? false : true;
    }
    
    protected function __wakeup() -> void
    {
    }

}