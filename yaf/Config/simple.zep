/**
 * Yaf Config Simple
 */
/**
 * @namespace
 */
namespace Yaf\Config;

class Simple extends \Yaf\Config_Abstract implements \Iterator, \ArrayAccess, \Countable
{
    /**
     * Used when unsetting values during iteration to ensure we do not skip
     * the next element
     *
     * @var boolean
     */
    protected _skipNextIteration;
    /**
     * Yaf_Config_Simple provides a property based interface to
     * an array. The data are read-only unless $readonly
     * is set to true on construction.
     *
     * Yaf_Config_Simple also implements Countable and Iterator to
     * facilitate easy access to the data.
     *
     * @param  array   $array
     * @param  boolean $readonly
     * @return void
     */
    public function __construct(array config, boolean readonly = false)
    {
        var key, value;

        if is_array(config) {
            
            let this->_config =  [];
            for key, value in config {                
                if is_array(value) {
                    let this->_config[key] = new self(value, readonly);
                } else {
                    let this->_config[key] = value;
                }
            }
        } else {
            throw new \Yaf\Exception\TypeError("Invalid parameters provided, must be an array");
        }
        //if (is_bool(readonly)) {
        let this->_readonly =  readonly;
    }
    
    /**
     * Defined by Countable interface
     *
     * @return int
     */
    public function count() -> int
    {
        
        return count(this->_config);
    }
    
    /**
     * Defined by Iterator interface
     *
     * @return mixed
     */
    public function current()
    {
        let this->_skipNextIteration =  false;
        
        return current(this->_config);
    }
    
    /**
     * Magic function so that $obj->value will work.
     *
     * @param string $name
     * @return mixed
     */
    public function __get(string name)
    {
        
        return this->get(name);
    }
    
    /**
     * Support isset() overloading on PHP 5.1
     *
     * @param string $name
     * @return boolean
     */
    public function __isset(string name) -> boolean
    {
        
        return isset this->_config[name];
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
     * Return a config value specified by name
     * @param  string $name
     * @return mixed
     */
    public function offsetGet(string name)
    {
        
        return this->__get(name);
    }
    
    /**
     * Set a key of the config with value
     * @param  string $name
     * @param  string $value
     * @throws Yaf_Config_Exception
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
     * @throws Yaf_Config_Exception
     * @return void
     */
    public function offsetUnset(string name)
    {
        if !this->readonly() {
            unset(this->_config[name]);
        } else {
        }
    }
    
    /**
     * Defined by Iterator interface
     *
     * @return mixed
     */
    public function key()
    {
        
        return key(this->_config);
    }
    
    /**
     * Defined by Iterator interface
     *
     */
    public function next()
    {
        if this->_skipNextIteration {
            let this->_skipNextIteration =  false;
            return;
        }
        next(this->_config);
    }
    
    /**
     * Defined by Iterator interface
     *
     */
    public function rewind() -> void
    {
        let this->_skipNextIteration =  false;
        reset(this->_config);
    }
    
    /**
     * Only allow setting of a property if $readonly
     * was set to true on construction. Otherwise, throw an exception.
     *
     * @param  string $name
     * @param  mixed  $value
     * @throws Yaf_Config_Exception
     * @return void
     */
    public function __set(string name, value)
    {
        if !this->readonly() {
            if is_string(name) {
                if is_array(value) {
                    let this->_config[name] = new self(value, false);
                } else {
                    let this->_config[name] = value;
                }
            } else {
                throw new Exception("Expect a string key name");
            }
        } else {
        }
    }
    
    /**
     * Return an associative array of the stored data.
     *
     * @return array
     */
    public function toArray() -> array
    {
        var myArray, data, key, value;
        
        let myArray =  [];
        let data =  this->_config;
        for key, value in data {
            
            if (value instanceof Simple) {
                let myArray[key] = value->toArray();
            } else {
                let myArray[key] = value;
            }
        }
        
        return myArray;
    }
    
    /**
     * Defined by Iterator interface
     *
     * @return boolean
     */
    public function valid() -> boolean
    {
        var key;
    
        let key =  key(this->_config);
        
        return key == null || key == false ? false : true;
    }
    
    /**
     * Support unset() overloading on PHP 5.1
     *
     * @param  string $name
     * @throws Yaf_Config_Exception
     * @return void
     */
    public function __unset(string name)
    {
        if !this->readonly() {
            unset(this->_config[name]);
            
            let this->_skipNextIteration =  true;
        } else {
            throw new Exception("Config is read only");
        }
    }
    
    /**
     * Retrieve a value and return $default if there is no element set.
     *
     * @param string $name
     * @param mixed $default
     * @return mixed
     */
    public function get(string name)
    {
        var result;
    
        let result =  false;
        
        if array_key_exists(name, this->_config) {
            let result = this->_config[name];
        }
        
        if is_array(result) {
            let result =  new self(result, this->readonly());
        }
        
        return result;
    }
    
    /**
     * Only allow setting of a property if $readonly
     * was set to true on construction. Otherwise, throw an exception.
     *
     * @param  string $name
     * @param  mixed  $value
     * @throws Yaf_Config_Exception
     * @return void
     */
    public function set(string name, value)
    {
        
        return this->__set(name, value);
    }
    
    /**
     * Merge two arrays recursively, overwriting keys of the same name
     * in $firstArray with the value in $secondArray.
     *
     * @param  mixed $firstArray  First array
     * @param  mixed $secondArray Second array to merge into first array
     * @return array
     */
    protected function _arrayMergeRecursive(firstArray, secondArray) -> array
    {
        var key, value;
        if is_array(firstArray) && is_array(secondArray) {
            for key, value in secondArray {
                
                if isset firstArray[key] {
                    let firstArray[key] = this->_arrayMergeRecursive(firstArray[key], value);
                } else {
                    if key === 0 {
                        let firstArray =  [0 : this->_arrayMergeRecursive(firstArray, value)];
                    } else {
                        let firstArray[key] = value;
                    }
                }
            }
        } else {
            let firstArray = secondArray;
        }
        
        return firstArray;
    }

}