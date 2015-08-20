package jcuda.jcurand;





import static org.junit.Assert.assertTrue;

import org.junit.Test;

/**
 * Basic test of the bindings of the JCurand class 
 */
public class JCurandBasicBindingTest
{
    public static void main(String[] args)
    {
        JCurandBasicBindingTest test = new JCurandBasicBindingTest();
        test.testJCurand();
    }

    @Test
    public void testJCurand()
    {
        assertTrue(BasicBindingTest.testBinding(JCurand.class));
    }
    
}
