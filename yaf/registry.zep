/**
 * Yaf Registry
 */
/**
 * @namespace
 */
namespace Yaf;

class Registry
{
    /**
     * the data array
     * @var array
     */
    protected static _entrys ;
    /**
     * @set undefined data
     * @param string $index
     * @param mixed $value
     * @return void
     */
    public static function set(name, value)
    {
        let self::_entrys[name] = value;
    }
    
    /**
     * @get variables
     * @param mixed $index
     * @return mixed
     */
    public static function get(name)
    {
        if self::has(name) {
            
            return self::_entrys[name];
        } else {
            
            return null;
        }
    }
    
    /**
     * check if the variable is in the registry
     * @param mixed $index
     * @return mixed
     */
    public static function has(name)
    {
        return isset self::_entrys[name];
    }
    
    /**
     * @del variables
     * @param mixed $index
     * @return mixed
     */
    public static function del(name)
    {
        if isset self::_entrys[name] {
            unset(self::_entrys[name]);
        
        }
    }

}